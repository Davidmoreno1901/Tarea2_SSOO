#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

using namespace cv;

//escala de grises utilizando el metodo de luminosidad  (Luminosity Method).
void convertToGrayscaleRegion(const Mat& colorImage, Mat& grayscaleImage, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < colorImage.cols; ++j) {
            Vec3b intensity = colorImage.at<Vec3b>(i, j);
            grayscaleImage.at<uchar>(i, j) = 0.21 * intensity[2] + 0.72 * intensity[1] + 0.07 * intensity[0];
        }
    }
}

// escala de grises utilizando el metodo de luminosidad paralelo
Mat convertToGrayscaleParallel(const Mat& colorImage, int numThreads) {
    Mat grayscaleImage(colorImage.rows, colorImage.cols, CV_8UC1);

    // almacenar hebras
    std::vector<std::thread> threads;

    //cantidad de filas por hebra
    int rowsPerThread = colorImage.rows / numThreads;

    // iniciar las hebras
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? colorImage.rows : (i + 1) * rowsPerThread;
        threads.emplace_back(convertToGrayscaleRegion, std::ref(colorImage), std::ref(grayscaleImage), startRow, endRow);
    }

    // esperar a que todas las hebras terminen
    for (auto& thread : threads) {
        thread.join();
    }

    return grayscaleImage;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_hebras>" << std::endl;
        return -1;
    }

    //imagen de entrada
    Mat colorImage = imread(argv[1], IMREAD_COLOR);

    if (!colorImage.data) {
        std::cerr << "Error al leer la imagen de entrada." << std::endl;
        return -1;
    }

    //n° hebras 
    int numThreads = std::stoi(argv[3]);

    // tiempo de ejecucion
    auto start = std::chrono::high_resolution_clock::now();

    // Convertir la imagen a escala de grises de manera paralela
    Mat grayscaleImage = convertToGrayscaleParallel(colorImage, numThreads);

    // Guardar la imagen resultante
    imwrite(argv[2], grayscaleImage);

    // fin tiempo de ejecucion
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // imprimir tiempo 
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;

    return 0;
}
