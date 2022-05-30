//
// Created by User on 27.04.2022.
//

#ifndef LABA17_C____SFML_VIEW_H
#define LABA17_C____SFML_VIEW_H

using namespace sf;

void zoomView(Vector2i pixel, RenderWindow& window, float zoom)
{
    const Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
    View view{ window.getView() };
    view.zoom(zoom);
    window.setView(view);
    const Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
    const Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);
//    const Vector2f centerCoord{ view.getCenter() };
//    std::cout << centerCoord.x << " " << centerCoord.y << std::endl;
    window.setView(view);
}


View getCoordinate(float x, float y) {
    View view;
    view.setCenter(x,y);
    return view;
}



#endif //LABA17_C____SFML_VIEW_H
