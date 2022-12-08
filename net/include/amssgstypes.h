#pragma once

#include <Eigen/Dense>

// ams-serialize
enum MeasurementType {
    UV_OFF = 0,
    UV_INVALID = 1,
    UV_UNRESOLVED = 2,
    UV_RESOLVED_COM = 3,
    UV_RESOLVED_SRV = 4,
};
enum SensorType {
    C_NONE = 0,
    C_NFOV_SE3 = 1,      // Pose Basis is NFOV Only
    C_WFOV_SE3 = 2,      // Pose Basis is WFOV Only
    C_STEREO_SIM3 = 3,   // Pose Basis is STEREO
    C_UFOV_SE3 = 4,      // Pose Basis is UFOV Only
    C_INAV_PREDICT = 5,  // Pose Basis is INAV
};
enum VPPSAvailable {
    UNDETERMINED = 0,
    NFOV1 = 1,
    NFOV2 = 2,
    WFOV = 3,
    LWIRN = 4,
    LWIRU1 = 5,
    LWIRU2 = 6,
    SPARE3 = 7,
    SPARE4 = 8,
    SPARE5 = 9,
    SPARE6 = 10,
    DEFAULT = 11,  // NEVER CHANGE THIS
};
struct PoseFiltCentroidMeasBus {
    uint32_t id;
    MeasurementType measurement_type;
    double validity_time;
    Eigen::Vector2d y;
    Eigen::Matrix2d r;
    uint32_t npix;
    bool clipped;
};
struct HelixLibCentroidMeasCRC {
    HelixLibCentroidMeasCRC() : centroid_meas(6) {}
    std::vector<PoseFiltCentroidMeasBus> centroid_meas;
    uint32_t crc32;
};
struct PoseFiltAERMeasBus {
    uint32_t id;
    MeasurementType measurement_type;
    double validity_time;
    Eigen::Vector3d y;
    Eigen::Matrix3d r;
    uint32_t npix;
    bool clipped;
};
struct HelixLibAERMeasCRC {
    HelixLibAERMeasCRC() : aer_meas(2) {}
    std::vector<PoseFiltAERMeasBus> aer_meas;
    uint32_t crc32;
};
struct PoseFiltNFTMeasBus {
    SensorType sensor_type;
    uint32_t seq;
    uint32_t valid_count;
    uint32_t kf;
    uint32_t feat_count;
    double validity_time;
    uint32_t health;
    Eigen::Matrix4d c;
    Eigen::Matrix<double, 7, 7> p;
    double cf_range;
    uint32_t cf_id;
};
struct HelixLibNFTMeasCRC {
    HelixLibNFTMeasCRC() : nft_meas(2) {}
    std::vector<PoseFiltNFTMeasBus> nft_meas;
    uint32_t crc32;
};

struct HelixLibVPPSOpModeConfig {
    HelixLibVPPSOpModeConfig() : config_stereo(2), config_trifocal(3) {}
    bool enable;
    VPPSAvailable config_monocular;
    std::vector<VPPSAvailable> config_stereo;
    std::vector<VPPSAvailable> config_trifocal;
};
struct HelixLibCameraConfig {
    bool centroid;
    bool lost_in_space;
    bool cmu;
    uint8_t save_images;
    uint8_t calibrate;
};
struct HelixLibCameraSuite {
    HelixLibCameraSuite() : camera_suite_buses(6) {}
    std::vector<HelixLibCameraConfig> camera_suite_buses;
};
struct HelixLibVPPSRelNavConfig {
    HelixLibVPPSRelNavConfig() : config_3dof(2), config_6dof(2) {}
    std::vector<HelixLibVPPSOpModeConfig> config_3dof;  // 50 Bytes
    std::vector<HelixLibVPPSOpModeConfig> config_6dof;  // 50 Bytes
    HelixLibCameraSuite camera_suite;                   // 30 Bytes
    uint32_t crc32;                                     // 4 Bytes
};

struct HelixLibRelNavInputs {
    /**
     * HelixLibRelNavInputs Struct Definition (1922 Bytes in Total)
     */
    HelixLibCentroidMeasCRC centroid;  // 418 Bytes
    HelixLibAERMeasCRC aer_3dof;       // 238 Bytes
    HelixLibNFTMeasCRC nft_pose_6dof;  // 1132 Bytes
    HelixLibVPPSRelNavConfig config;   // 134 Bytes
};

// svg2
struct GncInputBus
{
    uint32_t seq;
    double gpsTime;
    double sunToRsoSrv[3];

    /*
     * Camera
     * Eye: 3, 7, 11
     * Rot Matrix: 0, 1, 2, 4, 5, 6, 8, 9, 10
     */
    double chsToRsoSrv[4][4];
    double oofToEciPos[3];
    double oofToEciAtt[4];
    double lookatSrv[3];

    //added
    HelixLibRelNavInputs _elixLibRelNavInputs;

}; // __attribute__((packed));