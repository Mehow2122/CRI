#include "cri.h"
#include "ui_cri.h"
#include <iostream>
#include <vector>
#include "Spectrum.h"
#include <math.h>
#include "defines.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <cstdlib>
#include <fstream>
#include <tgmath.h>
#include <QTimer>

#define COUNT 20
#define SIZE_SP 113
using namespace std;
static Spectrum TSC[SIZE_TSC];
static Spectrum xyz_bar[3];
static Spectrum Wavelength;
double input_uvY[3][SIZE_TSC];
double reference_uvY[3][SIZE_TSC];
double CRITable[COUNT];
double CCTTable[COUNT];
int counter=0;
QString pathToFile;
int timerTime = 0;
void TscInit(){
    /*
     * Create table with value of TSC (TCS?) Wavelength - 360 to 830 with step 5
     *                                                    380-730
     */
    double tab[SIZE_TSC][SIZE] = {
            /*{0.116, 0.136, 0.159, 0.19, */{0.219, 0.239, 0.252, 0.256, 0.256, 0.254, 0.252, 0.248, 0.244, 0.24,  0.237, 0.232, 0.23,  0.226, 0.225, 0.222, 0.22,  0.218, 0.216, 0.214, 0.214, 0.214, 0.216, 0.218, 0.223, 0.225, 0.226, 0.226, 0.225, 0.225, 0.227, 0.23,  0.236, 0.245, 0.253, 0.262, 0.272, 0.283, 0.298, 0.318, 0.341, 0.367, 0.39,  0.409, 0.424, 0.435, 0.442, 0.448, 0.45,  0.451, 0.451, 0.451, 0.451, 0.451, 0.45,  0.45,  0.451, 0.451, 0.453, 0.454, 0.455, 0.457, 0.458, 0.46,  0.462, 0.463, 0.464, 0.465, 0.466, 0.466, 0.466},//,, 0.466, 0.467, 0.467, 0.467, 0.467, 0.467, 0.467, 0.467, 0.467, 0.467, 0.467, 0.467, 0.466, 0.466, 0.466, 0.466, 0.466, 0.465, 0.464, 0.464},
            /*{0.053, 0.055, 0.059, 0.064, */{0.07,  0.079, 0.089, 0.101, 0.111, 0.116, 0.118, 0.12,  0.121, 0.122, 0.122, 0.122, 0.123, 0.124, 0.127, 0.128, 0.131, 0.134, 0.138, 0.143, 0.15,  0.159, 0.174, 0.19,  0.207, 0.225, 0.242, 0.253, 0.26,  0.264, 0.267, 0.269, 0.272, 0.276, 0.282, 0.289, 0.299, 0.309, 0.322, 0.329, 0.335, 0.339, 0.341, 0.341, 0.342, 0.342, 0.342, 0.341, 0.341, 0.339, 0.339, 0.338, 0.338, 0.337, 0.336, 0.335, 0.334, 0.332, 0.332, 0.331, 0.331, 0.33,  0.329, 0.328, 0.328, 0.327, 0.326, 0.325, 0.324, 0.324, 0.324},//, 0.323, 0.322, 0.321, 0.32,  0.318, 0.316, 0.315, 0.315, 0.314, 0.314, 0.313},//, 0.313, 0.312, 0.312, 0.311, 0.311, 0.311, 0.311, 0.311, 0.31},
            /*{0.058, 0.059, 0.061, 0.063, */{0.065, 0.068, 0.07,  0.072, 0.073, 0.073, 0.074, 0.074, 0.074, 0.073, 0.073, 0.073, 0.073, 0.073, 0.074, 0.075, 0.077, 0.08,  0.085, 0.094, 0.109, 0.126, 0.148, 0.172, 0.198, 0.221, 0.241, 0.26,  0.278, 0.302, 0.339, 0.37,  0.392, 0.399, 0.4,   0.393, 0.38,  0.365, 0.349, 0.332, 0.315, 0.299, 0.285, 0.272, 0.264, 0.257, 0.252, 0.247, 0.241, 0.235, 0.229, 0.224, 0.22,  0.217, 0.216, 0.216, 0.219, 0.224, 0.23,  0.238, 0.251, 0.269, 0.288, 0.312, 0.34,  0.366, 0.39,  0.412, 0.431, 0.447, 0.46},//,  0.472, 0.481, 0.488, 0.493, 0.497, 0.5,   0.502, 0.505, 0.51,  0.516, 0.52},//,  0.524, 0.527, 0.531, 0.535, 0.539, 0.544, 0.548, 0.552, 0.555},
            /*{0.057, 0.059, 0.062, 0.067, */{0.074, 0.083, 0.093, 0.105, 0.116, 0.121, 0.124, 0.126, 0.128, 0.131, 0.135, 0.139, 0.144, 0.151, 0.161, 0.172, 0.186, 0.205, 0.229, 0.254, 0.281, 0.308, 0.332, 0.352, 0.37,  0.383, 0.39,  0.394, 0.395, 0.392, 0.385, 0.377, 0.367, 0.354, 0.341, 0.327, 0.312, 0.296, 0.28,  0.263, 0.247, 0.229, 0.214, 0.198, 0.185, 0.175, 0.169, 0.164, 0.16,  0.156, 0.154, 0.152, 0.151, 0.149, 0.148, 0.148, 0.148, 0.149, 0.151, 0.154, 0.158, 0.162, 0.165, 0.168, 0.17,  0.171, 0.17,  0.168, 0.166, 0.164, 0.164},//, 0.165, 0.168, 0.172, 0.177, 0.181, 0.185, 0.189, 0.192, 0.194, 0.197, 0.2},//,   0.204, 0.21,  0.218, 0.225, 0.233, 0.243, 0.254, 0.264, 0.274},
            /*{0.143, 0.187, 0.233, 0.269, */{0.295, 0.306, 0.31,  0.312, 0.313, 0.315, 0.319, 0.322, 0.326, 0.33,  0.334, 0.339, 0.346, 0.352, 0.36,  0.369, 0.381, 0.394, 0.403, 0.41,  0.415, 0.418, 0.419, 0.417, 0.413, 0.409, 0.403, 0.396, 0.389, 0.381, 0.372, 0.363, 0.353, 0.342, 0.331, 0.32,  0.308, 0.296, 0.284, 0.271, 0.26,  0.247, 0.232, 0.22,  0.21,  0.2,   0.194, 0.189, 0.185, 0.183, 0.18,  0.177, 0.176, 0.175, 0.175, 0.175, 0.175, 0.177, 0.18,  0.183, 0.186, 0.189, 0.192, 0.195, 0.199, 0.2,   0.199, 0.198, 0.196, 0.195, 0.195},//, 0.196, 0.197, 0.2,   0.203, 0.205, 0.208, 0.212, 0.215, 0.217, 0.219},//, 0.222, 0.226, 0.231, 0.237, 0.243, 0.249, 0.257, 0.265, 0.273, 0.28},
            /*{0.079, 0.081, 0.089, 0.113, */{0.151, 0.203, 0.265, 0.339, 0.41,  0.464, 0.492, 0.508, 0.517, 0.524, 0.531, 0.538, 0.544, 0.551, 0.556, 0.556, 0.554, 0.549, 0.541, 0.531, 0.519, 0.504, 0.488, 0.469, 0.45,  0.431, 0.414, 0.395, 0.377, 0.358, 0.341, 0.325, 0.309, 0.293, 0.279, 0.265, 0.253, 0.241, 0.234, 0.227, 0.225, 0.222, 0.221, 0.22,  0.22,  0.22,  0.22,  0.22,  0.223, 0.227, 0.233, 0.239, 0.244, 0.251, 0.258, 0.263, 0.268, 0.273, 0.278, 0.281, 0.283, 0.286, 0.291, 0.296, 0.302, 0.313, 0.325, 0.338, 0.351, 0.364, 0.376},//, 0.389, 0.401, 0.413, 0.425, 0.436, 0.447, 0.458, 0.469, 0.477, 0.485},//, 0.493, 0.5,   0.506, 0.512, 0.517, 0.521, 0.525, 0.529, 0.532, 0.535},
            /*{0.15,  0.177, 0.218, 0.293, */{0.378, 0.459, 0.524, 0.546, 0.551, 0.555, 0.559, 0.56,  0.561, 0.558, 0.556, 0.551, 0.544, 0.535, 0.522, 0.506, 0.488, 0.469, 0.448, 0.429, 0.408, 0.385, 0.363, 0.341, 0.324, 0.311, 0.301, 0.291, 0.283, 0.273, 0.265, 0.26,  0.257, 0.257, 0.259, 0.26,  0.26,  0.258, 0.256, 0.254, 0.254, 0.259, 0.27,  0.284, 0.302, 0.324, 0.344, 0.362, 0.377, 0.389, 0.4,   0.41,  0.42,  0.429, 0.438, 0.445, 0.452, 0.457, 0.462, 0.466, 0.468, 0.47,  0.473, 0.477, 0.483, 0.489, 0.496, 0.503, 0.511, 0.518, 0.525},//, 0.532, 0.539, 0.546, 0.553, 0.559, 0.565, 0.57,  0.575, 0.578, 0.581},//, 0.583, 0.585, 0.587, 0.588, 0.589, 0.59,  0.59,  0.59,  0.591, 0.592},
            /*{0.075, 0.078, 0.084, 0.09,  */{0.104, 0.129, 0.17,  0.24,  0.319, 0.416, 0.462, 0.482, 0.49,  0.488, 0.482, 0.473, 0.462, 0.45,  0.439, 0.426, 0.413, 0.397, 0.382, 0.366, 0.352, 0.337, 0.325, 0.31,  0.299, 0.289, 0.283, 0.276, 0.27,  0.262, 0.256, 0.251, 0.25,  0.251, 0.254, 0.258, 0.264, 0.269, 0.272, 0.274, 0.278, 0.284, 0.295, 0.316, 0.348, 0.384, 0.434, 0.482, 0.528, 0.568, 0.604, 0.629, 0.648, 0.663, 0.676, 0.685, 0.693, 0.7,   0.705, 0.709, 0.712, 0.715, 0.717, 0.719, 0.721, 0.72,  0.719, 0.722, 0.725, 0.727, 0.729},//, 0.73,  0.73,  0.73,  0.73,  0.73,  0.73,  0.73,  0.73,  0.73,  0.73},//,  0.73,  0.731, 0.731, 0.731, 0.731, 0.731, 0.731, 0.731, 0.731, 0.731},
            /*{0.069, 0.072, 0.073, 0.07,  */{0.066, 0.062, 0.058, 0.055, 0.052, 0.052, 0.051, 0.05,  0.05,  0.049, 0.048, 0.047, 0.046, 0.044, 0.042, 0.041, 0.038, 0.035, 0.033, 0.031, 0.03,  0.029, 0.028, 0.028, 0.028, 0.029, 0.03,  0.03,  0.031, 0.031, 0.032, 0.032, 0.033, 0.034, 0.035, 0.037, 0.041, 0.044, 0.048, 0.052, 0.06,  0.076, 0.102, 0.136, 0.19,  0.256, 0.336, 0.418, 0.505, 0.581, 0.641, 0.682, 0.717, 0.74,  0.758, 0.77,  0.781, 0.79,  0.797, 0.803, 0.809, 0.814, 0.819, 0.824, 0.828, 0.83,  0.831, 0.833, 0.835, 0.836, 0.836},//, 0.837, 0.838, 0.839, 0.839, 0.839, 0.839, 0.839, 0.839, 0.839, 0.839},//, 0.839, 0.839, 0.839, 0.839, 0.839, 0.838, 0.837, 0.837, 0.836, 0.836},
            /*{0.042, 0.043, 0.045, 0.047, */{0.05,  0.054, 0.059, 0.063, 0.066, 0.067, 0.068, 0.069, 0.069, 0.07,  0.072, 0.073, 0.076, 0.078, 0.083, 0.088, 0.095, 0.103, 0.113, 0.125, 0.142, 0.162, 0.189, 0.219, 0.262, 0.305, 0.365, 0.416, 0.465, 0.509, 0.546, 0.581, 0.61,  0.634, 0.653, 0.666, 0.678, 0.687, 0.693, 0.698, 0.701, 0.704, 0.705, 0.705, 0.706, 0.707, 0.707, 0.707, 0.708, 0.708, 0.71,  0.711, 0.712, 0.714, 0.716, 0.718, 0.72,  0.722, 0.725, 0.729, 0.731, 0.735, 0.739, 0.742, 0.746, 0.748, 0.749, 0.751, 0.753, 0.754, 0.755},//, 0.755, 0.755, 0.755, 0.756, 0.757, 0.758, 0.759, 0.759, 0.759, 0.759},//, 0.759, 0.759, 0.759, 0.759, 0.759, 0.758, 0.757, 0.757, 0.756, 0.756},
            /*{0.074, 0.079, 0.086, 0.098, */{0.111, 0.121, 0.127, 0.129, 0.127, 0.121, 0.116, 0.112, 0.108, 0.105, 0.104, 0.104, 0.105, 0.106, 0.11,  0.115, 0.123, 0.134, 0.148, 0.167, 0.192, 0.219, 0.252, 0.291, 0.325, 0.347, 0.356, 0.353, 0.346, 0.333, 0.314, 0.294, 0.271, 0.248, 0.227, 0.206, 0.188, 0.17,  0.153, 0.138, 0.125, 0.114, 0.106, 0.1,   0.096, 0.092, 0.09,  0.087, 0.085, 0.082, 0.08,  0.079, 0.078, 0.078, 0.078, 0.078, 0.081, 0.083, 0.088, 0.093, 0.102, 0.112, 0.125, 0.141, 0.161, 0.182, 0.203, 0.223, 0.242, 0.257, 0.27},//,  0.282, 0.292, 0.302, 0.31,  0.314, 0.317, 0.323, 0.33,  0.334, 0.338},//, 0.343, 0.348, 0.353, 0.359, 0.365, 0.372, 0.38,  0.388, 0.396, 0.403},
            /*{0.189, 0.175, 0.158, 0.139, */{0.12,  0.103, 0.09,  0.082, 0.076, 0.068, 0.064, 0.065, 0.075, 0.093, 0.123, 0.16,  0.207, 0.256, 0.3,   0.331, 0.346, 0.347, 0.341, 0.328, 0.307, 0.282, 0.257, 0.23,  0.204, 0.178, 0.154, 0.129, 0.109, 0.09,  0.075, 0.062, 0.051, 0.041, 0.035, 0.029, 0.025, 0.022, 0.019, 0.017, 0.017, 0.017, 0.016, 0.016, 0.016, 0.016, 0.016, 0.016, 0.016, 0.016, 0.018, 0.018, 0.018, 0.018, 0.019, 0.02,  0.023, 0.024, 0.026, 0.03,  0.035, 0.043, 0.056, 0.074, 0.097, 0.128, 0.166, 0.21,  0.257, 0.305, 0.354},//, 0.401, 0.446, 0.485, 0.52,  0.551, 0.577, 0.599, 0.618, 0.633, 0.645},//, 0.656, 0.666, 0.674, 0.68,  0.686, 0.691, 0.694, 0.697, 0.7,   0.702},
            /*{0.071, 0.076, 0.082, 0.09,  */{0.104, 0.127, 0.161, 0.211, 0.264, 0.313, 0.341, 0.352, 0.359, 0.361, 0.364, 0.365, 0.367, 0.369, 0.372, 0.374, 0.376, 0.379, 0.384, 0.389, 0.397, 0.405, 0.416, 0.429, 0.443, 0.454, 0.461, 0.466, 0.469, 0.471, 0.474, 0.476, 0.483, 0.49,  0.506, 0.526, 0.553, 0.582, 0.618, 0.651, 0.68,  0.701, 0.717, 0.729, 0.736, 0.742, 0.745, 0.747, 0.748, 0.748, 0.748, 0.748, 0.748, 0.748, 0.748, 0.748, 0.747, 0.747, 0.747, 0.747, 0.747, 0.747, 0.747, 0.746, 0.746, 0.746, 0.745, 0.744, 0.743, 0.744, 0.745},//, 0.748, 0.75,  0.75,  0.749, 0.748, 0.748, 0.747, 0.747, 0.747, 0.747},//, 0.746, 0.746, 0.746, 0.746, 0.745, 0.745, 0.745, 0.745, 0.745, 0.745},
            /*{0.036, 0.036, 0.036, 0.036, */{0.036, 0.036, 0.037, 0.038, 0.039, 0.039, 0.04,  0.041, 0.042, 0.042, 0.043, 0.044, 0.044, 0.045, 0.045, 0.046, 0.047, 0.048, 0.05,  0.052, 0.055, 0.057, 0.062, 0.067, 0.075, 0.083, 0.092, 0.1,   0.108, 0.121, 0.133, 0.142, 0.15,  0.154, 0.155, 0.152, 0.147, 0.14,  0.133, 0.125, 0.118, 0.112, 0.106, 0.101, 0.098, 0.095, 0.093, 0.09,  0.089, 0.087, 0.086, 0.085, 0.084, 0.084, 0.084, 0.084, 0.085, 0.087, 0.092, 0.096, 0.102, 0.11,  0.123, 0.137, 0.152, 0.169, 0.188, 0.207, 0.226, 0.243, 0.26},//,  0.277, 0.294, 0.31,  0.325, 0.339, 0.353, 0.366, 0.379, 0.39,  0.399},//, 0.408, 0.416, 0.422, 0.428, 0.434, 0.439, 0.444, 0.448, 0.451, 0.454},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1,1, 1, 1, 1, 1}



    };
    for(int i=0;i<SIZE_TSC;i++)
    {
        TSC[i].setData(tab[i]);
    }


}
void xyzBarInit(){
    double tab[3][SIZE] = {
            { /*0.0001,0.0002,0.0004,0.0007,*/0.0014,0.0022,0.0042,0.0077,0.0143,0.0232,0.0435,0.0776,0.1344,0.2148,0.2839,0.3285,0.3483,0.3481,0.3362,0.3187,0.2908,0.2511,0.1954,0.1421,0.0956,0.0580,0.0320,0.0147,0.0049,0.0024,0.0093,0.0291,0.0633,0.1096,0.1655,0.2258,0.2904,0.3597,0.4335,0.5121,0.5945,0.6784,0.7621,0.8425,0.9163,0.9786,1.0263,1.0567,1.0622,1.0456,1.0026,0.9384,0.8545,0.7514,0.6424,0.5419,0.4479,0.3608,0.2835,0.2187,0.1649,0.1212,0.0874,0.0636,0.0468,0.0329,0.0227,0.0158,0.0114,0.0081,0.0058,0.0041,0.0029,0.0020,0.0014},//,0.0010,0.0007,0.0005,0.0003,0.0002,0.0002,0.0002,0.0001,0.0001,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
            { /*0.0000,0.0000,0.0000,0.0000,*/0.0000,0.0001,0.0001,0.0002,0.0004,0.0006,0.0012,0.0022,0.0040,0.0073,0.0116,0.0168,0.0230,0.0298,0.0380,0.0480,0.0600,0.0739,0.0910,0.1126,0.1390,0.1693,0.2080,0.2586,0.3230,0.4073,0.5030,0.6082,0.7100,0.7932,0.8620,0.9149,0.9540,0.9803,0.9950,1.0000,0.9950,0.9786,0.9520,0.9154,0.8700,0.8163,0.7570,0.6949,0.6310,0.5668,0.5030,0.4412,0.3810,0.3210,0.2650,0.2170,0.1750,0.1380,0.1070,0.0816,0.0610,0.0446,0.0320,0.0232,0.0170,0.0119,0.0082,0.0057,0.0041,0.0029,0.0021,0.0015,0.0010,0.0007,0.0005},//,0.0004,0.0002,0.0002,0.0001,0.0001,0.0001,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000},
            { /*0.0006,0.0011,0.0019,0.0035,*/0.0006,0.0106,0.0201,0.0362,0.0679,0.1102,0.2074,0.3713,0.6456,1.0391,1.3856,1.6230,1.7471,1.7826,1.7721,1.7441,1.6692,1.5281,1.2876,1.0419,0.8130,0.6162,0.4652,0.3533,0.2720,0.2123,0.1582,0.1117,0.0783,0.0573,0.0422,0.0298,0.0203,0.0134,0.0088,0.0058,0.0039,0.0028,0.0021,0.0018,0.0017,0.0014,0.0011,0.0010,0.0008,0.0006,0.0003,0.0002,0.0002,0.0001,0.0005,0.0003,0.0002,0.0001,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000}//,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000}
    };
    for(int i=0;i<3;i++)
    {
        xyz_bar[i].setData(tab[i]);
    }

}
Spectrum getData(QString &pathToFile){
    Spectrum Data;
    /*
     * Get Data from spectrometer
     */

    string str= "exec " + pathToFile.toStdString()+"/bin/spotread -e -N -H -O -s data.sp";
    const char *c = str.c_str();
    system(c);
    fstream fs;
    fs.open ("data.sp", fstream::in);
    string line;
    getline(fs,line);
    getline(fs,line);

    string::size_type sz;
    double a;
    vector <double> output;
         fs.close();

    replace(line.begin(), line.end(), '.', ',');

    for(int i=0;i<SIZE_SP;i++)
    {
        a=stod(line,&sz);
        line=line.substr(sz);
        output.push_back(a);
    }
    output.erase(output.begin(),output.begin()+7);

      //cout<<line;
    int i=0;
    for (vector<double>::iterator it = output.begin() ; it != output.end(); it++)
        {
           if(i%2==1){
            *it=(*it+*(it+1))/2;
            output.erase(it+1);
           }
           cout<<*it<<" "<<i+1<<endl;
           i++;
        }




    //double tab[SIZE] = {/*0,0,0,0,*/0.005883458,0.003153768,0.002428677,0.005087091,0.003232818,0.003487637,0.00369248,0.005209241,0.007479133,0.013097946,0.023971671,0.04330206,0.082721167,0.141231868,0.234004159,0.342052302,0.439128498,0.448697658,0.375497636,0.278293162,0.194531977,0.141683533,0.112335847,0.103018715,0.114389761,0.145538096,0.189716767,0.251895814,0.310723777,0.359981034,0.382088604,0.376106021,0.346534325,0.308036724,0.260159458,0.216220023,0.174484972,0.135613979,0.10873008,0.085992361,0.068631638,0.058752863,0.052765794,0.055485988,0.072911542,0.153199437,0.387537401,0.817543224,1,0.647943604,0.213755255,0.037105254,0.017615101,0.014653118,0.013849082,0.014657157,0.013470592,0.014247679,0.012157914,0.012093381,0.011553132,0.010619949,0.010147794,0.008642115,0.009513861,0.007869817,0.008414764,0.007418679,0.006377112,0.005564827,0.005900156};//,0.004168186,0.004222223,0.003457765,0.003368788,0.002989992,0.003670466,0.00340568,0.002611528,0.002588501,0.002936635,0.004015998,0.001159704,0.002090916,0.002778291,0,0,0,0,0,0};
    Data.setData(&output);
    //Data.setData(tab);
    //cout<<sizeof(tab)<<" "<<output.size();
    return Data;

};
void setWavelength() {
    double tab[SIZE];
    for(int i=0;i<SIZE;i++)
    {
        tab[i] = 360+i*5;
    }
    Wavelength.setData(tab);

}
Spectrum normalizeSpectrum(Spectrum &data){

    Spectrum output;
    double sum = 0;
    vector <double> dataValue = data.getData();
    vector <double> xyzValue = xyz_bar[1].getData();

    for (int i=0;i<SIZE;i++) {
        sum += dataValue[i] * xyzValue[i];
    }
    for(int i = 0; i<SIZE; i++){
        dataValue[i] = (dataValue[i]/sum)*100;
    }
    //vector <double> tab[SIZE];
    output.setData(&dataValue);
    return output;
}
void calculate_uv(Spectrum &Data, double (&uvY)[3][SIZE_TSC]){
    double tab[3][SIZE];
    double x, y;
    double xyz[3][SIZE_TSC];
    for(int i=0;i<SIZE_TSC;i++)
    {
        for (int k = 0; k<3;k++) {
            xyz[k][i]=0;
            for(int j=0;j<SIZE;j++){
                tab[k][j] = TSC[i].getData()[j]*Data.getData()[j]*xyz_bar[k].getData()[j];
                xyz[k][i]+=tab[k][j];
            }

        }
        x=xyz[0][i]/(xyz[0][i]+xyz[1][i]+xyz[2][i]);
        y=xyz[1][i]/(xyz[0][i]+xyz[1][i]+xyz[2][i]);

        uvY[0][i]=4*x/(-2*x+12*y+3);
        uvY[1][i]=6*y/(-2*x+12*y+3);
        uvY[2][i]=xyz[1][i];
    }
}
double calculateCCT(Spectrum &normalizeData){
    double CCT;
    double X=0,Y=0,Z=0;//,u,v;
    for(int i=0;i<SIZE;i++)
    {
        X+=normalizeData.getData()[i]*xyz_bar[0].getData()[i];
        Y+=normalizeData.getData()[i]*xyz_bar[1].getData()[i];
        Z+=normalizeData.getData()[i]*xyz_bar[2].getData()[i];
    }
//    u = 4*X/(X+15*Y+3*Z);
//    v = 6*X/(X+15*Y+3*Z);
    double x = X/(X+Y+Z);
    double y = Y/(X+Y+Z);
    double xe = 0.3320;
    double ye = 0.1858;
    double n = ((x-xe)/(y-ye));
    double CCT_value = -449*pow(n,3)+3524*pow(n,2)-6823.3*n+5520.33;
    return CCT_value;
    //Approximation:
    //CCT(x, y) = ?449n3 + 3525n2 ? 6823.3n + 5520.33,
    // n = (x ? xe)/(y ? ye) is the inverse slope line, and (xe = 0.3320, ye = 0.1858) is the "epicenter"
}
Spectrum caluclateBlackBodyPlancktian(double &CCT){

/*
 * h = 6.62607E-34
 * c= 3*10E8
 * kB = 1.38065E-23; -- Boltzman constant
 * 2hc^2 = 1.1926926E-14
 * hc/kB = 0.0143977184659399558179118531126643247745627059718248
 *
 */
    double hc  = 1.1926926E-16;
    double hckB =0.0143977;
    vector <double> tab;

    double mianownik;
    for (int i=0;i<SIZE;i++) {
        mianownik = pow(Wavelength.getData()[i]*0.000000001,5)*(exp(hckB/(Wavelength.getData()[i]*0.000000001*CCT))-1);

        tab.push_back(hc/(mianownik));
    }
    Spectrum BlackBody;
    BlackBody.setData(&tab);
    return BlackBody;
    //$I$2/((A5*0,000000001)^5)/(EXP($I$3/(A5*0,000000001*$I$1))-1)

/*
     * 2hc^2/(lambda^5 * e^(hc/lambda*kBT)-1)
    */
}
Spectrum calculateBlackBodyDaylight(double &CCT){
    double xD, yD, M1, M2;
    Spectrum BlackBody;
    double s[3][SIZE]=
    {
        /*{61.50,65.15,68.80,66.10,*/{63.40,64.60,65.80,80.30,94.80,99.80,104.80,105.35,105.90,101.35,96.80,105.35,113.90,119.75,125.60,125.55,125.50,123.40,121.30,121.30,121.30,117.40,113.50,113.30,113.10,111.95,110.80,108.65,106.50,107.65,108.80,107.05,105.30,104.85,104.40,102.20,100.00,98.00,96.00,95.55,95.10,92.10,89.10,89.80,90.50,90.40,90.30,89.35,88.40,86.20,84.00,84.55,85.10,83.50,81.90,82.25,82.60,83.75,84.90,83.10,81.30,76.60,71.90,73.10,74.30,75.35,76.40,69.85,63.30,67.50,71.70},//,74.35,77.00,71.10,65.20,56.45,47.70,58.15,68.60,66.80,65.00,65.50,66.00,63.50,61.00,57.15,53.30,56.10,58.90,60.40,61.90},
        /*{38.00,40.20,42.40,40.45,*/{38.50,36.75,35.00,39.20,43.40,44.85,46.30,45.10,43.90,40.50,37.10,36.90,36.70,36.30,35.90,34.25,32.60,30.25,27.90,26.10,24.30,22.20,20.10,18.15,16.20,14.70,13.20,10.90,8.60,7.35,6.10,5.15,4.20,3.05,1.90,0.95,0.00,-0.80,-1.60,-2.55,-3.50,-3.50,-3.50,-4.65,-5.80,-6.50,-7.20,-7.90,-8.60,-9.05,-9.50,-10.20,-10.90,-10.80,-10.70,-11.35,-12.00,-13.00,-14.00,-13.80,-13.60,-12.80,-12.00,-12.65,-13.30,-13.10,-12.90,-11.75,-10.60,-11.10,-11.60},//,-11.90,-12.20,-11.20,-10.20,-9.00,-7.80,-9.50,-11.20,-10.80,-10.40,-10.50,-10.60,-10.15,-9.70,-9.00,-8.30,-8.80,-9.30,-9.55,-9.80},
        /*{5.30,5.70,6.10,4.55,*/{3.00,2.10,1.20,0.05,-1.10,-0.80,-0.50,-0.60,-0.70,-0.95,-1.20,-1.90,-2.60,-2.75,-2.90,-2.85,-2.80,-2.70,-2.60,-2.60,-2.60,-2.20,-1.80,-1.65,-1.50,-1.40,-1.30,-1.25,-1.20,-1.10,-1.00,-0.75,-0.50,-0.40,-0.30,-0.15,0.00,0.10,0.20,0.35,0.50,1.30,2.10,2.65,3.20,3.65,4.10,4.40,4.70,4.90,5.10,5.90,6.70,7.00,7.30,7.95,8.60,9.20,9.80,10.00,10.20,9.25,8.30,8.95,9.60,9.05,8.50,7.75,7.00,7.30,7.60}//,7.80,8.00,7.35,6.70,5.95,5.20,6.30,7.40,7.10,6.80,6.90,7.00,6.70,6.40,5.95,5.50,5.80,6.10,6.30,6.50}
    };
    if(CCT>7000){
        xD = -2.0064*pow(10,9)/pow(CCT,3) + 1.9018*pow(10,6)/pow(CCT,2) + 0.24748 *1000/CCT + 0.237040;
    }
    else{
        xD = -4.6070 * pow(10,9) / pow(CCT,3) + 2.9678*pow(10,6)/pow(CCT,2) + 0.09911*1000/CCT + 0.244063;
    }
    yD = -3.000*pow(xD,2) + 2.870*xD -0.275;


    M1 = (-1.3515- 1.7703*xD + 5.9114*yD )/ (0.0241 + 0.2562*xD - 0.7341*yD);
    M2 = (0.0300 - 31.44243*xD + 30.0717*yD) / (0.0241 + 0.2562*xD - 0.7341*yD );
   // cout<<"CCT: "<<CCT<<" xD = "<<xD<< " yD = "<<yD<<" M1 = "<<M1<<" M2 = "<<M2;
    vector <double> tab[SIZE];
    for (int i=0;i<SIZE;i++){
        tab->push_back(s[0][i]+s[1][i]*M1+s[2][i]*M2);
    }

    BlackBody.setData(tab);
    return BlackBody;
    /*
     * S(lambda) = S0(lambda) + M1S1(lambda) + M2S2(lambda)
     * M1 = (-1.3515- 1.7703*xo + 5.9114*yD )/ (0.0241 + O.2562*xD - 0.7341*yD )
     * M2 = (0.0300 - 31.44243*xD + 30.0717yD) / (0.0241 + O.2562*xD - 0.7341*yD )
     *
     * Dla CCT 4000K : 7000K
     * xD = (-4.6070 * 10^9 / CCT^3) + 2,9678*10&6/CCT^2 + 0,09911*10^3 / CCT + 0,244063
     * Dla CCT > 7000K
     * xD = -2,0064*10^9/CCT^3 + 1,9018*10^6/CCT^2 + 0,24748 *10^3 / CCT + 0,237040
     * yD  =  -3,000*xD^2 + 2,870*xD -0,275
     *
     */

}
void chromaticyAdaptation(double uvY[3][SIZE_TSC], double Uk, double Vk, double Ur, double Vr, double (&uvk)[3][SIZE_TSC]) {
    double ck = (4-Uk-10*Vk)/Vk;
    double dk = (1.708*Vk+0.404-1.481*Uk)/Vk;
    double cr = (4-Ur-10*Vr)/Vr;
    double dr = (1.708*Vr+0.404-1.481*Ur)/Vr;
    double cdr[2][SIZE_TSC];
    for(int i=0;i<SIZE_TSC;i++)
    {
        cdr[0][i]=(4- uvY[0][i]-10* uvY[1][i])/ uvY[1][i];
        cdr[1][i]=(1.708* uvY[1][i]+0.404-1.481* uvY[0][i])/ uvY[1][i];

    }
    for(int i=0;i<SIZE_TSC;i++)
    {
        uvk[0][i]=(10.872+0.404*cr/ck*cdr[0][i]-4*dr/dk*cdr[1][i])/(16.518+1.481*cr/ck*cdr[0][i]-dr/dk*cdr[1][i]);
        uvk[1][i]=5.52/(16.518+1.481*cr/ck*cdr[0][i]-dr/dk*cdr[1][i]);
        uvk[2][i]=uvY[2][i];
    }


}

void calculateRTable(double input_uvk[3][SIZE_TSC], double reference_uvY[3][SIZE_TSC], double (&R)[SIZE_TSC])
{
    double W[2][SIZE_TSC];
    double U[2][SIZE_TSC];
    double V[2][SIZE_TSC];
    double deltaE[SIZE_TSC];
    for(int i=0;i<SIZE_TSC;i++)
    {
        W[0][i]=25*pow(input_uvk[2][i],(double)1/3)-17;
        W[1][i]=25*pow(reference_uvY[2][i],(double)1/3)-17;
        U[0][i]=13*W[0][i]*(input_uvk[0][i]- input_uvk[0][SIZE_TSC-1]);
        U[1][i]=13*W[1][i]*(reference_uvY[0][i]-reference_uvY[0][SIZE_TSC-1]);
        V[0][i]=13*W[0][i]*(input_uvk[1][i]- input_uvk[1][SIZE_TSC-1]);
        V[1][i]=13*W[1][i]*(reference_uvY[1][i]-reference_uvY[1][SIZE_TSC-1]);
        deltaE[i]=sqrt(pow((W[0][i]-W[1][i]),2)+pow((U[0][i]-U[1][i]),2)+pow((V[0][i]-V[1][i]),2));
        R[i]=100-4.6*deltaE[i];

    }

}
double calculateCRI(double R[SIZE_TSC])
{
    double CRI = 0;
    for(int i=0;i<8;i++)
    {
        CRI+=R[i];
    }
    CRI/=8.0;
    return CRI;
}

CRI::CRI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CRI)
{
    ui->setupUi(this);
    TscInit();
    setWavelength();
    xyzBarInit();


}

CRI::~CRI()
{
    delete ui;
}

void CRI::serialData(){

    Spectrum Data = getData(pathToFile);
    Spectrum normalize = normalizeSpectrum(Data);
    Spectrum BlackBody;
    calculate_uv(normalize,input_uvY);
    double CCT = calculateCCT(normalize);
    if(CCT < 5000){
        BlackBody = caluclateBlackBodyPlancktian(CCT);
    }
    else{
        BlackBody = calculateBlackBodyDaylight(CCT);
    }
    BlackBody = normalizeSpectrum(BlackBody);
    calculate_uv(BlackBody,reference_uvY);
    double input_uvk[3][SIZE_TSC];
    double R[SIZE_TSC];
    chromaticyAdaptation(input_uvY,input_uvY[0][SIZE_TSC-1],input_uvY[1][SIZE_TSC-1],reference_uvY[0][SIZE_TSC-1],reference_uvY[1][SIZE_TSC-1],input_uvk);
    calculateRTable(input_uvk, reference_uvY, R);
    CRITable[counter] = calculateCRI(R);
    CCTTable[counter] = CCT;
    counter++;



}

void CRI::on_pushButton_clicked()
{
        pathToFile = ui->lineEdit->text();

        Spectrum Data = getData(pathToFile);
        Spectrum normalize = normalizeSpectrum(Data);
        Spectrum BlackBody;
        calculate_uv(normalize,input_uvY);
        double CCT = calculateCCT(normalize);
        if(CCT < 5000){
            BlackBody = caluclateBlackBodyPlancktian(CCT);
        }
        else{
            BlackBody = calculateBlackBodyDaylight(CCT);
        }
        BlackBody = normalizeSpectrum(BlackBody);
        calculate_uv(BlackBody,reference_uvY);
        double input_uvk[3][SIZE_TSC];
        double R[SIZE_TSC];
        chromaticyAdaptation(input_uvY,input_uvY[0][SIZE_TSC-1],input_uvY[1][SIZE_TSC-1],reference_uvY[0][SIZE_TSC-1],reference_uvY[1][SIZE_TSC-1],input_uvk);
        calculateRTable(input_uvk, reference_uvY, R);
        double CRI = calculateCRI(R);


        QMessageBox::information(this,"Measure:","CCT: "+QString::number(CCT)+
                    "\n\nR1: " + QString::number(R[0])+
                    "\nR2: " + QString::number(R[1])+
                    "\nR3: " + QString::number(R[2])+
                    "\nR4: " + QString::number(R[3])+
                    "\nR5: " + QString::number(R[4])+
                    "\nR6: " + QString::number(R[5])+
                    "\nR7: " + QString::number(R[6])+
                    "\nR8: " + QString::number(R[7])+
                    "\nR9: " + QString::number(R[8])+
                    "\nR10: " + QString::number(R[9])+
                    "\nR11: " + QString::number(R[10])+
                    "\nR12: " + QString::number(R[11])+
                    "\nR13: " + QString::number(R[12])+
                    "\nR14: " + QString::number(R[13])+
                    "\n\nCRI: "+QString::number(CRI));

}

void CRI::on_Exit_Button_clicked()
{
    QApplication::quit();
}

void CRI::on_Calibrate_button_clicked()
{
    QString a = ui->lineEdit->text();
    string b= "exec " + a.toStdString()+"/bin/spotread -e -N -H -O -s data.sp";

    const char *c = b.c_str();//string c = b.toStdString();
    //char c[] = "ls";
    system(c);

    //In future I will use popen to eliminate errors
/*
    FILE *lsofFile_p = popen(c,"r");
        char buffer[10024];
        string out;
        string dwa="retry:\n";
        while(fgets(buffer, sizeof(buffer), lsofFile_p)!=NULL){
            out+=buffer;
        }
    if(!out.substr(out.length()-6,out.length()).compare("retry:"))
        QMessageBox::information(this,"Error",QString::number(out.length()));
*/
    //QString Test = QString::fromStdString(asdf);
    //QMessageBox::information(this,"title",QString::number(asdf));
}

void test(){

            qDebug()<<timerTime;
}
void zeroTable(){

    for(int i=0;i<COUNT;i++)
       {
        CRITable[i]=0;
        CCTTable[i]=0;
        }
}
void CRI::printCRITable(){
    QMessageBox msgBox;
    QString outputText = "";
    for(int i=0;i<COUNT;i++){
        outputText+="Measurement "+QString::number(i+1)+":  "+QString::number(CRITable[i])+" CCT: "+QString::number(CCTTable[i]) + "\n";

    }
    msgBox.setText(outputText);
    msgBox.exec();

}

void CRI::on_Serial_Button_clicked()
{
     pathToFile = ui->lineEdit->text();
     QString textTime = ui->spinBox->text();
     timerTime = textTime.toInt();
     //time = time2;
    zeroTable();
    counter=0;
     for(int i=0;i<COUNT;i++)
     {
        QTimer::singleShot((timerTime*1000*i), this, SLOT(serialData()));

     }
     QTimer::singleShot((timerTime*1000*COUNT),this, SLOT(printCRITable()));
}
