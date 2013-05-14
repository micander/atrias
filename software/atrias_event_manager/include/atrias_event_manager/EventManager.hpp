#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

/** 
  * @file EventManager.hpp
  * @author Ryan Van Why
  * @brief This contains the main class for the Event Manager component.
  */

// Orocos
#include <rtt/Component.hpp>            // We're a component
#include <rtt/ConnPolicy.hpp>           // So we can subscribe to and publish to ROS topics
#include <rtt/InputPort.hpp>            // Allows us to receive events from RT Ops
#include <rtt/OutputPort.hpp>           // Allows us to form ports to the GUI and Controller Manager
#include <rtt/TaskContext.hpp>          // We're a component aka a TaskContext

// ATRIAS
#include <atrias_msgs/rt_ops_event.h>   // So we can receive and transmit event messages
#include <atrias_shared/EventManip.hpp> // For the event::Event type as well as various metadata types

namespace atrias {

namespace eventManager {

class EventManager : public RTT::TaskContext {
	public:
		/** @brief Initializes this component.
		  * @param name This component's name.
		  */
		EventManager (std::string const &name);
	
		/** @brief This forwards an event to the Controller Manager.
		  * @param event The event to be forwarded.
		  */
		void sendCM(atrias_msgs::rt_ops_event &event);

		/** @brief This forwards an event to the GUI.
		  * @param event The event to be forwarded.
		  */
		void sendGUI(atrias_msgs::rt_ops_event &event);

	private:
		/** @brief This is the event output port to the Controller Manager.
		  */
		RTT::OutputPort<atrias_msgs::rt_ops_event> cmOut;

		/** @brief This is how we receive events from RT Ops.
		  */
		RTT::InputPort<atrias_msgs::rt_ops_event> eventsIn;

		/** @brief This is the output port to the GUI.
		  */
		RTT::OutputPort<atrias_msgs::rt_ops_event> guiOut;

		/** @brief This processes a new event.
		  */
		void eventInCallback(RTT::base::PortInterface* portInterface);
};

}

}

#endif // EVENTMANAGER_HPP

// vim: noexpandtab