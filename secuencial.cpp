#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

using namespace cv;

// funcion convertir a escala de grises utilizando el metodo de luminosidad  (Luminosity Method)
Mat convertToGrayscale(const Mat& colorImage) {
    Mat grayscaleImage(colorImage.rows, colorImage.cols, CV_8UC1);

    for (int i = 0; i < colorImage.rows; ++i) {
        for (int j = 0; j < colorImage.cols; ++j) {
            Vec3b intensity = colorImage.at<Vec3b>(i, j);
            grayscaleImage.at<uchar>(i, j) = 0.21 * intensity[2] + 0.72 * intensity[1] + 0.07 * intensity[0];
        }
    }

    return grayscaleImage;
}

//main
int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << std::endl;
        return -1;
    }

    // lee  imagen de entrada
    Mat colorImage = imread(argv[1], IMREAD_COLOR);

    if (!colorImage.data) {
        std::cerr << "Error al leer la imagen de entrada." << std::endl;
        return -1;
    }

    // tiempo 
    auto start = std::chrono::high_resolution_clock::now();

    // convertir imagen a escala de grises
    Mat grayscaleImage = convertToGrayscale(colorImage);

    // guardar imagen 
    imwrite(argv[2], grayscaleImage);

    // tiempo  ejecucion
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // imprimir  tiempo 
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;

    return 0;
}