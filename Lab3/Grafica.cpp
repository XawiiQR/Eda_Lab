#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <float.h>
#include <cstdlib>
#include "Octree.cpp"

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>

using namespace std;

vtkSmartPointer<vtkActor> createCubeActor(double x, double y, double z) {
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    cubeSource->SetXLength(1.0);
    cubeSource->SetYLength(1.0);
    cubeSource->SetZLength(1.0);
    cubeSource->SetCenter(x, y, z);
    cubeSource->Update();
    
    vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
    
    vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(1.0, 1.0, 1.0);
    
    return cubeActor;
}

vector<vector<double>> leer()
{
    ifstream Archivo("/Users/javierquisperojas/Javi_UNSA/6to semestre/Estructura de datos avanzados/Eda Lab/Lab3/points2.csv");
    string linea;
    vector<vector<double>> vec;
    
    if (!Archivo.is_open())
        {
            cerr << "Error al abrir el archivo." << endl;
            return {}; // Devolver un vector vacío en caso de error
        }
    else
        {
            while (getline(Archivo, linea))
                {
                    vector<double> fila;
                    string word;
                    
                    for (int i = 0; i < linea.size(); i++)
                        {
                            if (linea[i] == ',')
                                {
                                    fila.push_back(stod(word));
                                    word.clear();
                                }
                            else
                                {
                                    word += linea[i];
                                }
                        }
                    
                    // Agregar el último elemento de la línea
                    fila.push_back(stod(word));
                    
                    vec.push_back(fila);
                }
        }
    
    return vec;
}

void search(OctreeNode* node, vtkSmartPointer<vtkRenderer> renderer) {
    if (node == nullptr) {
        return;
    }
    
    for (const auto& point : node->points) {
        //std::cout << "Point: (" << point.x << ", " <<  << ", " << point.z << ")\n";
        vtkSmartPointer<vtkActor> cubeActor = createCubeActor(point.x , point.y, point.z );
        renderer->AddActor(cubeActor);
    }
    
    for (int i = 0; i < 8; ++i) {
        search(node->children[i], renderer);
    }
}
void setupRenderer(vtkSmartPointer<vtkRenderer> renderer, std::vector<std::vector<double>> coordinates ) {
    
    
    // Encontrar el rango de coordenadas
    double minX = DBL_MAX, maxX = -DBL_MAX;
    double minY = DBL_MAX, maxY = -DBL_MAX;
    double minZ = DBL_MAX, maxZ = -DBL_MAX;
    
    for (const auto &point : coordinates) {
        minX = std::min(minX, point[0]);
        maxX = std::max(maxX, point[0]);
        minY = std::min(minY, point[1]);
        maxY = std::max(maxY, point[1]);
        minZ = std::min(minZ, point[2]);
        maxZ = std::max(maxZ, point[2]);
    }
    /*
    // Configurar la cámara
    renderer->GetActiveCamera()->SetPosition((maxX + minX) / 2.0, (maxY + minY) / 2.0, (maxZ + minZ) / 2.0);
    
    double sceneRadius = std::max({maxX - minX, maxY - minY, maxZ - minZ}) / 2.0;
    renderer->GetActiveCamera()->SetClippingRange(sceneRadius / 100.0, sceneRadius * 100.0);
    */
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
    //renderer->SetBackground(colors->GetColor3d("Silver").GetData());
    
    
    Point min(minX, minY,minZ);
    Point max(maxX,maxY, maxZ);
    Octree octree(min, max);
    for(const auto &puntos : coordinates){
        octree.insert(Point(puntos[0], puntos[1],puntos[2]));
    }
    search(octree.root,renderer);
    //octree.exit();
}


int main()
{
    
    
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    renderWindow->SetSize(1600, 1200);  // Ajusta según tus necesidades

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(1);
    renderer->GetActiveCamera()->Elevation(10);
    renderer->ResetCameraClippingRange();
    //renderer->SetBackground(colors->GetColor3d("Silver").GetData());
    
    std::vector<std::vector<double>> coordinates = leer();
    setupRenderer(renderer, coordinates);
    
    renderWindow->Render();
    renderWindow->SetWindowName("Javier WIlber Quispe Rojas");
    renderWindowInteractor->Start();

    return 0;
}
