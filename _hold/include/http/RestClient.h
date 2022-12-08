//
// Created by Daniel St. John on 9/30/21.
//

#pragma  once

#include <string>
#include <curl/curl.h>
#include <mutex>
#include <functional>


namespace lm {

    class RestClient {
    public:
        std::string get (std::string uri);
        void getAsync(std::string uri, std::function< void(std::string) > f);

        std::string post (std::string uri, const char *payload);
        void postAsync(std::string uri, const char *payload, std::function< void(std::string) > f);

        RestClient();
    private:
        void validate(CURL *curl);
        void validate( CURLcode ret);
     };

    class RestClient2  
		{
		public:
			//RestClient();

			static std::string  Get(std::string uri);
			static std::shared_ptr<std::thread> Get(std::string uri, std::function< void(std::string) > f);
			static std::string  Post(std::string uri, const char* payload);
			static std::shared_ptr<std::thread> Post(std::string uri, const char* payload, std::function< void(std::string) > f);

		protected:
			static void validate(CURL* curl);
			static void validate(CURLcode ret);
		};
}


