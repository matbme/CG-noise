#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include <noise/noise.h>
#include <noise/noiseutils.h>

using namespace noise;

struct HeightMapParams {
    int width;
    int height;
    std::array<float, 4> bounds;
    int octave;
    float frequency;
    float persistance;
};

utils::NoiseMap BuildAHeightMap(HeightMapParams& params) {
    module::Perlin myModule;
    utils::NoiseMap heightMap;

    if (params.octave >= 0) myModule.SetOctaveCount(params.octave);
    if (params.frequency >= 0) myModule.SetFrequency(params.frequency);
    if (params.persistance >= 0) myModule.SetPersistence(params.persistance);

    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule (myModule);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetDestSize (params.width, params.height);
    heightMapBuilder.SetBounds (params.bounds[0], params.bounds[1], params.bounds[2], params.bounds[3]);
    heightMapBuilder.Build ();

    return heightMap;
}

void RenderHeightMap(utils::NoiseMap heightMap, std::string filename,
                     std::function<void(utils::RendererImage&)> biome_gen = nullptr)
{
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);

    renderer.ClearGradient ();
    if (biome_gen == nullptr) { // Bioma default
        renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
        renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
        renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
        renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
        renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
        renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
        renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
        renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow

        renderer.EnableLight ();
        renderer.SetLightContrast (3);
        renderer.SetLightBrightness (2);
    } else {
        biome_gen(renderer); // Bioma customizado
    }

    renderer.Render ();

    utils::WriterBMP writer;
    writer.SetSourceImage (image);
    writer.SetDestFilename (filename.c_str());
    writer.WriteDestFile ();
}

void Ex1() {
    // Exercicio 1: Renderizar 4 mapas vizinhos
    std::array<utils::NoiseMap, 4> heightmaps; // Nossos heightmaps
    std::array<HeightMapParams, 4> params = {
        1024, 1024, {2.0,  6.0, 1.0, 5.0}, -1, -1, -1,
        1024, 1024, {6.0, 10.0, 1.0, 5.0}, -1, -1, -1,
        1024, 1024, {2.0,  6.0, 5.0, 9.0}, -1, -1, -1,
        1024, 1024, {6.0, 10.0, 5.0, 9.0}, -1, -1, -1,
    };

    int it = 0;
    for(auto heightmap : heightmaps) {
        heightmap = BuildAHeightMap(params[it]);
        std::string filename = "../Ex1-" + std::to_string(++it) + ".bmp";
        RenderHeightMap(heightmap, filename);
    }
}

void Ex2() {
    // Exercicio 2: Experimentar oitavas, frequencia e persistencia diferentes
    std::array<utils::NoiseMap, 8> heightmaps; // Nossos heightmaps
    std::array<HeightMapParams, 8> params = {
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 3,  6, 0.4,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 4,  8, 1.0,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 2,  3, 0.7,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 3, 10, 0.1,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 5, 11, 0.2,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 1, 16, 0.9,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 6,  6, 0.6,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 4, 12, 0.5,
    };

    int it = 0;
    for(auto heightmap : heightmaps) {
        heightmap = BuildAHeightMap(params[it]);
        std::string filename = "../Ex2-" + std::to_string(++it) + ".bmp";
        RenderHeightMap(heightmap, filename);
    }
}

void Ex3() {
    // Exercicio 3: Gerar dois mapeamentos de biomas diferentes
    std::array<utils::NoiseMap, 2> heightmaps; // Nossos heightmaps
    std::array<HeightMapParams, 2> params = {
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 6, 2, 0.45,
        1024, 1024, {2.0, 6.0, 1.0, 5.0}, 3, 5, 0.2,
    };

    // Um bioma estilo planicie
    auto pampa_gaucho = [](utils::RendererImage& renderer) {
        renderer.AddGradientPoint(-1.0000, utils::Color (104,  82,  66, 255)); // terra
        renderer.AddGradientPoint(-0.7000, utils::Color ( 30,  81,  40, 255)); // mato
        renderer.AddGradientPoint( 0.9000, utils::Color ( 78, 134,  44, 255)); // grama rasa
        renderer.AddGradientPoint( 1.0000, utils::Color (140, 133, 122, 255)); // pedra

        renderer.EnableLight();
        renderer.SetLightContrast(3);
        renderer.SetLightBrightness(2);
    };

    // Um bioma formando uma galaxia
    auto galaxia = [](utils::RendererImage& renderer) {
        renderer.AddGradientPoint(-1.0000, utils::Color ( 37,  29,  58, 255)); // espaço profundo
        renderer.AddGradientPoint( 0.4500, utils::Color ( 37,  29,  58, 255)); // espaço profundo
        renderer.AddGradientPoint( 0.5000, utils::Color ( 42,  37,  80, 255)); // espaço raso
        renderer.AddGradientPoint( 0.6000, utils::Color ( 87,  10,  87, 255)); // aquela cor roxa que tem sei la
        renderer.AddGradientPoint( 0.9950, utils::Color (255, 140,  50, 255)); // poeira cosmica
        renderer.AddGradientPoint( 1.0000, utils::Color (250, 237, 240, 255)); // estrela

        renderer.EnableLight();
        renderer.SetLightContrast(3);
        renderer.SetLightBrightness(2);
    };

    std::array<std::function<void(utils::RendererImage&)>, 2> biomas = {pampa_gaucho, galaxia};

    int it = 0;
    for(auto heightmap : heightmaps) {
        heightmap = BuildAHeightMap(params[it]);
        std::string filename = "../Ex3-" + std::to_string(it + 1) + ".bmp";
        RenderHeightMap(heightmap, filename, biomas[it++]);
    }
}

int main(int argc, char** argv) {
    Ex1();
    Ex2();
    Ex3();

    return EXIT_SUCCESS;
}
