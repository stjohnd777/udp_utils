#include "utils.h"

namespace lm {
    namespace  spp {

        std::string toBinaryString(char c) {
            return std::bitset<8>(c).to_string();
        }

        //template <class SomeStruct>
        //char* Serialize(SomeStruct& s) {
        //    size_t size = sizeof(SomeStruct);
        //    char* p = (char*)&s;
        //    return p;
        //}

        //// TODO: maybe shared_ptr
        //template <class SomeStruct>
        //SomeStruct* DeSerialize(char* src) {
        //    size_t len = sizeof(SomeStruct);
        //    char* dest = new char[len];
        //    memcpy(dest, src, len);
        //    SomeStruct* s = (SomeStruct*)(dest);
        //    return s;
        //}

        asio::ip::udp::endpoint utils::GetUdpEndpoint(std::string host, unsigned short port) {
            boost::system::error_code ec;
            // checks whether argument contains a valid IPv4 or IPv6 address then
            // instantiates a corresponding v4 || v6
            auto ip_address = asio::ip::address::from_string(host, ec);
            if (ec.value() != 0) {
                std::cout << ec.value() << std::endl;
                throw  ec.value();
            }
            auto ep = asio::ip::udp::endpoint(ip_address, port);
            return ep;
        }

       // 00000000 00000000 00000000 00000001 BE
        // 00000001 00000000 00000000 00000000 LE
        bool utils::IsLittleIndian() {
            unsigned int x = 1;
            char* c = (char*)&x;
            return *c ? true : false;
        }

        bool utils::IsBigIndian() {
            return !IsLittleIndian();
        }

        bool utils::OpenPGM_C(PGMImage* pgm, const char* filename) {

            // Open the image file in the 'read binary' mode
            FILE* pgmfile = fopen(filename, "rb");
            if (pgmfile == NULL) {
                printf("File does not exist\n");
                return false;
            }

            IgnoreComments(pgmfile);
            fscanf(pgmfile, "%s", pgm->pgmType);

            // Check for correct PGM Binary file type
            if (strcmp(pgm->pgmType, "P5")) {
                fprintf(stderr, "Wrong file type!\n");
                exit(EXIT_FAILURE);
            }

            IgnoreComments(pgmfile);

            // Read the image dimensions
            fscanf(pgmfile, "%d %d", &(pgm->width), &(pgm->height));

            IgnoreComments(pgmfile);

            // Read maximum gray value
            fscanf(pgmfile, "%d", &(pgm->maxValue));
            IgnoreComments(pgmfile);

            // Allocating memory to store
            // img info in defined struct
            //pgm->data = reinterpret_cast<char**> (  malloc(pgm->height * sizeof(unsigned char*)) );
            pgm->data = (unsigned char**)(malloc(pgm->height * sizeof(unsigned char*)));


            // Storing the pixel info in the struct
            if (pgm->pgmType[1] == '5') {
                fgetc(pgmfile); // int fgetc(FILE *stream) gets the next character 
                for (int i = 0; i < pgm->height; i++) {
                    pgm->data[i] = (unsigned char*)malloc(pgm->width * sizeof(unsigned char));
                    // If memory allocation is failed
                    if (pgm->data[i] == NULL) {
                        fprintf(stderr, "malloc failed\n");
                        exit(1);
                    }
                    // Read the gray values and write on allocated memory
                    fread(pgm->data[i], sizeof(unsigned char), pgm->width, pgmfile);
                }
            }
            fclose(pgmfile);
            return true;
        }

        char* utils::readFile_C(std::string fileName) {
            FILE* fileptr = fopen(fileName.c_str(), "rb"); // Open the file in binary mode
            fseek(fileptr, 0, SEEK_END); // Jump to the end of the file
            long filelen = ftell(fileptr); // Get the current byte offset in the file;
            rewind(fileptr); // Jump back to the beginning of the file
            char* buffer = new char[filelen * sizeof(char)]; // (char*)malloc(filelen * sizeof(char)); // Enough memory for the file
            fread(buffer, filelen, 1, fileptr); // Read in the entire file
            fclose(fileptr); // Close the file
            return buffer;
        }

        void utils::IgnoreComments(FILE* fp) {
            int ch;
            char line[100];
            // Ignore any blank lines
            while ((ch = fgetc(fp)) != EOF && isspace(ch));

            // Recursively ignore comments in a PGM image commented lines start with a '#'
            if (ch == '#') {
                fgets(line, sizeof(line), fp);
                // char *fgets(char *str, int n, FILE *stream) reads a line 
                // from the specified stream and stores it into the string pointed to by str. 
                // It stops when either (n-1) characters are read
                IgnoreComments(fp);
            }
            else {
                fseek(fp, -1, SEEK_CUR);
            }
        }

    }
}