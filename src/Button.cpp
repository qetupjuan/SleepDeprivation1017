#include "Button.h"

#include <utility>
#include "Game.h"
#include "Config.h"


Button::Button(const std::string& image_path, std::string button_name, const GameObjectType type,
               const glm::vec2 position, const bool is_centered):
m_alpha(255), m_name(std::move(button_name)), m_isCentered(is_centered),
m_mouseOver(false), m_mouseOverActive(false), m_mouseOutActive(false), m_active(true)
{
	TheTextureManager::Instance()->load(image_path,
		m_name, TheGame::Instance()->getRenderer());

	const auto size = TheTextureManager::Instance()->getTextureSize(m_name);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(position);
	setType(type);
}

Button::~Button()
= default;

void Button::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw(m_name, xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, m_alpha, true);
}

void Button::update()
{
	
}

void Button::clean()
{
}


void Button::setMousePosition(const glm::vec2 mouse_position)
{
	m_mousePosition = mouse_position;
}

void Button::setMouseButtonClicked(const bool clicked)
{
	m_mouseButtonClicked = clicked;
}


bool Button::m_eventExists(const Event id)
{
	return m_events.find(id) != m_events.end();
}


void Button::handleMouseEvents(SDL_Event* event)
{

		auto wheel = 0;
		if (event)
		{
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				m_mousePosition.x = event->motion.x;
				m_mousePosition.y = event->motion.y;

				if (CollisionManager::pointRectCheck(m_mousePosition, getPosition(), getWidth(), getHeight()))
				{
					m_mouseOver = true;
				}
				else
				{
					m_mouseOver = false;
				}


				if ((m_events[MOUSE_OVER]) && (!m_mouseOverActive))
				{
					if (m_mouseOver)
					{
						m_events[MOUSE_OVER](this);
						m_mouseOverActive = true;
					}
				}
				else if ((m_events[MOUSE_OVER]) && (!m_mouseOver))
				{
					m_mouseOverActive = false;
				}

				if ((m_events[MOUSE_OUT]) && (m_mouseOutActive) && (!m_mouseOver))
				{
					m_events[MOUSE_OUT](this);
					m_mouseOutActive = false;
				}
				else if ((m_events[MOUSE_OUT]) && (m_mouseOver))
				{
					m_mouseOutActive = true;
				}

				break;
			case SDL_MOUSEBUTTONDOWN:

				switch (event->button.button)
				{
				case SDL_BUTTON_LEFT:
					if ((m_events[CLICK]) && (m_mouseOver))
					{
						m_mouseButtonClicked = true;
						m_events[CLICK](this); // call click event
					}
					break;
				}

				break;
			case SDL_MOUSEBUTTONUP:
				switch (event->button.button)
				{
				case SDL_BUTTON_LEFT:
					m_mouseButtonClicked = false;
					break;
				}
				break;
			case SDL_MOUSEWHEEL:
				wheel = event->wheel.y;
				break;
			default:
				break;
			}
		}
}

bool Button::addEventListener(const Event event, const EventHandler handler)
{
	if(m_eventExists(event))
	{
		return false;
	}
	
	m_events[event] = handler;
	return true;
}

Button::EventHandler Button::getEventHandler(const Event event)
{
	return m_events[event];
}

void Button::setAlpha(const Uint8 alpha)
{
	m_alpha = alpha;
}

void Button::setActive(const bool value)
{
	m_active = value;
}
