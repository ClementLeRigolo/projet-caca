#pragma once

#include "libs.hpp"

void buildMainMenu();
void buildLevel1();

// Utility functions
sf::Vector2f getCenter(sf::Texture texture);
sf::Vector2f getCenter(float width, float height);
sf::Vector2f getCenter(sf::Shape &shape);
sf::Vector2f getCenter(sf::Text &shape);

sf::Vector2i getMousePosition(sf::RenderWindow& window);
bool DoMouseIntersect(sf::Vector2i mousePos, sf::FloatRect to_check);


// Randomisation
int randomNumber(int min_num, int max_num);
void modulateSound(sf::Sound* sound, float lowest, float highest);


// Button functions
void doNothingFunc();
void exempleFunc();
void buttonGoToSettingsFunc();
void buttonExitGameFunc();
void buttonPlayGameFunc();
void buttonBackMainMenuFunc();
void toggleVsyncFunc(bool toggle);

// Easing functions
double lerp(double a, double b, double t);
float damp(float source, float smoothing, float dt);
sf::Color smoothColor(sf::Color c1, sf::Color c2, double prog);
double clamp(double min, double max, double value);


// Vectors
sf::Vector2f v2uToV2f(sf::Vector2u vector);
sf::Vector2u v2fToV2u(sf::Vector2f vector);
sf::Vector2i v2fToV2i(sf::Vector2f vector);
sf::Vector2f v2iToV2f(sf::Vector2i vector);
sf::Vector2f vectAdd(sf::Vector2f v1, sf::Vector2f v2);
sf::Vector2f vectSub(sf::Vector2f v1, sf::Vector2f v2);
float vectMag(sf::Vector2f v);
sf::Vector2f vectMult(sf::Vector2f v, float n);
sf::Vector2f vectUnit(sf::Vector2f v);
sf::Vector2f vectFmult(sf::Vector2f v, sf::Vector2f v2);
sf::Vector2f vectNorm(sf::Vector2f v);
float vectDot(sf::Vector2f v1, sf::Vector2f v2);
float vectCross(sf::Vector2f v1, sf::Vector2f v2);
float distFrom(sf::Vector2f p1, sf::Vector2f p2);
sf::Vector2f closestPointSeg(sf::Vector2f a, sf::Vector2f b, sf::Vector2f p);


// sf::View
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);


// Min Max
float getMin(float a, float b);
float getMax(float a, float b);