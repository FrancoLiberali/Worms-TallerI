#ifndef _GAME_BUILDER_H
#define _GAME_BUILDER_H

#include <list>
#include "ProxyClient.h"
#include "view/mainView.h"

class GameBuilder {
private:
    mainView& view;
    ProxyClient& proxy;
public:
    GameBuilder(ProxyClient& proxy, mainView& view);
};
#endif