#pragma once

#ifndef _WIN64
# include <netinet/in.h>
#endif
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <mutex>
#include <cstring>
#include <time.h>

#include "../../network/NetworkManager.hpp"

#include "Client.hpp"
#include "Room.hpp"

#include "SoundManager.h"
#include "EventNetwork.h"
#include "BitArray.h"
#include "SceneLoader.h"
#include "RessourceManager.h"
#include "GameManager.h"
#include "TransformObject.h"
#include "IComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Collider.h"
#include "Script.h"
#include "Application.h"
