#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace cv;

// convertir a escala de grises utilizando el metodo de luminosidad  (Luminosity Method) de manera paralela con openmp
Mat convertToGrayscaleOpenMP(const Mat& colorImage) {
    Mat grayscaleImage(colorImage.rows, colorImage.cols, CV_8UC1);

    #pragma omp parallel for
    for (int i = 0; i < colorImage.rows; ++i) {
        for (int j = 0; j < colorImage.cols; ++j) {
            Vec3b intensity = colorImage.at<Vec3b>(i, j);
            grayscaleImage.at<uchar>(i, j) = 0.21 * intensity[2] + 0.72 * intensity[1] + 0.07 * intensity[0];
        }
    }

    return grayscaleImage;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << std::endl;
        return -1;
    }

    // imagen de entrada
    Mat colorImage = imread(argv[1], IMREAD_COLOR);

    if (!colorImage.data) {
        std::cerr << "Error al leer la imagen de entrada." << std::endl;
        return -1;
    }

    // tiempo de ejecucion
    auto start = std::chrono::high_resolution_clock::now();

    // imagen a escala de grises de manera paralela con openmp
    Mat grayscaleImage = convertToGrayscaleOpenMP(colorImage);

    // imagen resultante
    imwrite(argv[2], grayscaleImage);

    // fin tiempo de ejecucion
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // imprimir tiempo
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;

    return 0;
}
