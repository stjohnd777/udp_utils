
const MeasurementType = {
    UV_OFF: 0,
    UV_INVALID: 1,
    UV_UNRESOLVED: 2,
    UV_RESOLVED_COM: 3,
    UV_RESOLVED_SRV: 4,
}
 

const  SensorType = {
    C_NONE : 0,
    C_NFOV_SE3 : 1,      // Pose Basis is NFOV Only
    C_WFOV_SE3 : 2,      // Pose Basis is WFOV Only
    C_STEREO_SIM3 : 3,   // Pose Basis is STEREO
    C_UFOV_SE3 : 4,      // Pose Basis is UFOV Only
    C_INAV_PREDICT : 5,  // Pose Basis is INAV
}
 

 const VPPSAvailable = {
    UNDETERMINED :0,
    NFOV1 : 1,
    NFOV2 : 2,
    WFOV : 3,
    LWIRN : 4,
    LWIRU1 : 5,
    LWIRU2 : 6,
    SPARE3 : 7,
    SPARE4 : 8,
    SPARE5 : 9,
    SPARE6 : 10,
    DEFAULT : 11,  // NEVER CHANGE THIS
};
 



let GncInputBus = {
    seq: 0,
    gpsTime: 0,
    sunToRsoSrv: [1, 2, 3],
    chsToRsoSrv: [
        [1, 2, 3, 4],
        [1, 2, 3, 4],
        [1, 2, 3, 4],
        [1, 2, 3, 4],
    ],
    oofToEciPos: [1, 2, 3],
    oofToEciAtt: [1, 2, 3, 4],
    lookatSrv: [1, 2, 3],

    helixLibRelNavInputs: {

        centroid: {
            crc: 0,
            centroid_meas: [{
                id: 0,
                measurement_type: 0,
                validity_time: 0,
                y: [x1, x2];
                r: [[a11, a12], [a21, a22]],
                npix: 0,
                clipped: true
            },
            {
                id: 0,
                measurement_type: 0,
                validity_time: 0,
                y: [x1, x2];
                r: [[a11, a12], [a21, a22]],
                npix: 0,
                clipped: true
            },
            {
                id: 0,
                measurement_type: 0,
                validity_time: 0,
                y: [x1, x2];
                r: [[a11, a12], [a21, a22]],
                npix: 0,
                clipped: true
            },
            {
                id: 0,
                measurement_type: 0,
                validity_time: 0,
                y: [x1, x2];
                r: [[a11, a12], [a21, a22]],
                npix: 0,
                clipped: true
            },
            {
                id: 0,
                measurement_type: 0,
                validity_time: 0,
                y: [x1, x2];
                r: [[a11, a12], [a21, a22]],
                npix: 0,
                clipped: true
            },
            {
                id: 0,
                measurement_type: 0,
                validity_time: 0,
                y: [x1, x2];
                r: [[a11, a12], [a21, a22]],
                npix: 0,
                clipped: true
            }]
        },

        aer_3dof: {
            crc: 0,
            aer_meas: [
                {
                    id: 0,
                    measurement_type: 0,
                    validity_time: 0,
                    y: [1, 2, 3],
                    r: [[a11, a12, a13], [a21, a22, a23], [a31, a32, a33]],
                    npix: 0,
                    clipped: false
                },
                {
                    id: 0,
                    measurement_type: 0,
                    validity_time: 0,
                    y: [1, 2, 3],
                    r: [[a11, a12, a13], [a21, a22, a23], [a31, a32, a33]],
                    npix: 0,
                    clipped: false
                },
            ]
        },

        nft_pose_6dof: {
            crc32: 0,
            ntf_meas: [
                {
                    sensor_type: 0,
                    seq: 0,
                    valid_count: 0,
                    kf: 0,
                    feat_count: 0,
                    validity_time: 0,
                    health: 0,
                    c: [
                        [1, 2, 3, 4],
                        [1, 2, 3, 4],
                        [1, 2, 3, 4],
                        [1, 2, 3, 4],
                    ],
                    p: [
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                    ],
                    cf_range: 0,
                    cf_id: 0
                },
                {
                    sensor_type: 0,
                    seq: 0,
                    valid_count: 0,
                    kf: 0,
                    feat_count: 0,
                    validity_time: 0,
                    health: 0,
                    c: [
                        [1, 2, 3, 4],
                        [1, 2, 3, 4],
                        [1, 2, 3, 4],
                        [1, 2, 3, 4],
                    ],
                    p: [
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                        [1, 2, 3, 4, 5, 6, 7],
                    ],
                    cf_range: 0,
                    cf_id: 0
                },
            ]
        },

        config: {
            crc32: 0,
            config_3dof: {},
            config_6dof: {},
            camera_suite: {
                camera_suite_buses: [{
                    centroid: true,
                    lost_in_space: true,
                    cmu: true,
                    save_images: 0,
                    calibrate: 0
                },
                {
                    centroid: true,
                    lost_in_space: true,
                    cmu: true,
                    save_images: 0,
                    calibrate: 0
                },
                {
                    centroid: true,
                    lost_in_space: true,
                    cmu: true,
                    save_images: 0,
                    calibrate: 0
                },
                {
                    centroid: true,
                    lost_in_space: true,
                    cmu: true,
                    save_images: 0,
                    calibrate: 0
                },
                {
                    centroid: true,
                    lost_in_space: true,
                    cmu: true,
                    save_images: 0,
                    calibrate: 0
                },
                {
                    centroid: true,
                    lost_in_space: true,
                    cmu: true,
                    save_images: 0,
                    calibrate: 0
                },
                ]
            }

        }
    },


}
