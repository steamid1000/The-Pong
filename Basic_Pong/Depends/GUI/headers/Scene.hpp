#pragma once
#ifndef SFML_Graphics_hpp
    #include <SFML/Graphics.hpp>
#endif


class Scene
{
public:
    Scene();
    ~Scene();

    virtual void setup()=0;
    virtual void render()=0;
};

Scene::Scene(){}

Scene::~Scene(){}


