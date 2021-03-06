#ifndef _CPP_SHAPE_PREDICTOR_H_
#define _CPP_SHAPE_PREDICTOR_H_

#include "../export.h"
#include <dlib/image_processing/shape_predictor.h>
#include "../shared.h"
 
using namespace dlib;
using namespace std;

DLLEXPORT shape_predictor* shape_predictor_new()
{
    return new shape_predictor();
}

DLLEXPORT shape_predictor* deserialize_shape_predictor(const char* file_name)
{
    shape_predictor* predictor = new shape_predictor();
    dlib::deserialize(file_name) >> (*predictor);
    return predictor;
}

DLLEXPORT shape_predictor* deserialize_shape_predictor_proxy(proxy_deserialize* proxy)
{
    proxy_deserialize& p = *static_cast<proxy_deserialize*>(proxy);
    shape_predictor* predictor = new shape_predictor();
    p >> (*predictor);
    return predictor;
}

#pragma region shape_predictor_operator

DLLEXPORT int shape_predictor_operator(shape_predictor* predictor,
                                       array2d_type img_type,
                                       void* img,
                                       rectangle* rect,
                                       full_object_detection** full_obj_detect)
{
    int err = ERR_OK;
    *full_obj_detect = nullptr;

    switch(img_type)
    {
        case array2d_type::UInt8:
            {
                full_object_detection result = (*predictor)(*((array2d<uint8_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::UInt16:
            {
                full_object_detection result = (*predictor)(*((array2d<uint16_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::Int32:
            {
                full_object_detection result = (*predictor)(*((array2d<int32_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::Float:
            {
                full_object_detection result = (*predictor)(*((array2d<float>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::Double:
            {
                full_object_detection result = (*predictor)(*((array2d<double>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::RgbPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<rgb_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::HsiPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<hsi_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::RgbAlphaPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<rgb_alpha_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        default:
            err = ERR_INPUT_ARRAY_TYPE_NOT_SUPPORT;
            break;
    }

    return err;
}

DLLEXPORT int shape_predictor_matrix_operator(shape_predictor* predictor,
                                              matrix_element_type img_type,
                                              void* img,
                                              rectangle* rect,
                                              full_object_detection** full_obj_detect)
{
    int err = ERR_OK;
    *full_obj_detect = nullptr;

    switch(img_type)
    {
        case matrix_element_type::UInt8:
            {
                full_object_detection result = (*predictor)(*((matrix<uint8_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::UInt16:
            {
                full_object_detection result = (*predictor)(*((matrix<uint16_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::UInt32:
            {
                full_object_detection result = (*predictor)(*((matrix<uint32_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Int8:
            {
                full_object_detection result = (*predictor)(*((matrix<int8_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Int16:
            {
                full_object_detection result = (*predictor)(*((matrix<int16_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Int32:
            {
                full_object_detection result = (*predictor)(*((matrix<int32_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Float:
            {
                full_object_detection result = (*predictor)(*((matrix<float>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Double:
            {
                full_object_detection result = (*predictor)(*((matrix<double>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::RgbPixel:
            {
                full_object_detection result = (*predictor)(*((matrix<rgb_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::HsiPixel:
            {
                full_object_detection result = (*predictor)(*((matrix<hsi_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::RgbAlphaPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<rgb_alpha_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        default:
            err = ERR_MATRIX_ELEMENT_TYPE_NOT_SUPPORT;
            break;
    }

    return err;
}

DLLEXPORT int shape_predictor_operator_mmod_rect(shape_predictor* predictor,
                                                 array2d_type img_type,
                                                 void* img,
                                                 mmod_rect* rect,
                                                 full_object_detection** full_obj_detect)
{
    int err = ERR_OK;
    *full_obj_detect = nullptr;

    switch(img_type)
    {
        case array2d_type::UInt8:
            {
                full_object_detection result = (*predictor)(*((array2d<uint8_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::UInt16:
            {
                full_object_detection result = (*predictor)(*((array2d<uint16_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::Int32:
            {
                full_object_detection result = (*predictor)(*((array2d<int32_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::Float:
            {
                full_object_detection result = (*predictor)(*((array2d<float>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::Double:
            {
                full_object_detection result = (*predictor)(*((array2d<double>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::RgbPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<rgb_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::HsiPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<hsi_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case array2d_type::RgbAlphaPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<rgb_alpha_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        default:
            err = ERR_INPUT_ARRAY_TYPE_NOT_SUPPORT;
            break;
    }

    return err;
}

DLLEXPORT int shape_predictor_matrix_operator_mmod_rect(shape_predictor* predictor,
                                                        matrix_element_type img_type,
                                                        void* img,
                                                        mmod_rect* rect,
                                                        full_object_detection** full_obj_detect)
{
    int err = ERR_OK;
    *full_obj_detect = nullptr;

    switch(img_type)
    {
        case matrix_element_type::UInt8:
            {
                full_object_detection result = (*predictor)(*((matrix<uint8_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::UInt16:
            {
                full_object_detection result = (*predictor)(*((matrix<uint16_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::UInt32:
            {
                full_object_detection result = (*predictor)(*((matrix<uint32_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Int8:
            {
                full_object_detection result = (*predictor)(*((matrix<int8_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Int16:
            {
                full_object_detection result = (*predictor)(*((matrix<int16_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Int32:
            {
                full_object_detection result = (*predictor)(*((matrix<int32_t>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Float:
            {
                full_object_detection result = (*predictor)(*((matrix<float>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::Double:
            {
                full_object_detection result = (*predictor)(*((matrix<double>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::RgbPixel:
            {
                full_object_detection result = (*predictor)(*((matrix<rgb_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::HsiPixel:
            {
                full_object_detection result = (*predictor)(*((matrix<hsi_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        case matrix_element_type::RgbAlphaPixel:
            {
                full_object_detection result = (*predictor)(*((array2d<rgb_alpha_pixel>*)img), *rect);
                *full_obj_detect = new full_object_detection(result);
            }
            break;
        default:
            err = ERR_MATRIX_ELEMENT_TYPE_NOT_SUPPORT;
            break;
    }

    return err;
}

#pragma endregion shape_predictor_operator

DLLEXPORT unsigned int shape_predictor_num_parts(shape_predictor* predictor)
{
    return predictor->num_parts();
}

DLLEXPORT unsigned int shape_predictor_num_features(shape_predictor* predictor)
{
    return predictor->num_features();
}

DLLEXPORT void shape_predictor_delete(shape_predictor* obj)
{
	delete obj;
}

#endif