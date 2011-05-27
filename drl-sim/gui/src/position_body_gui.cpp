// Devin Koepl

#include <gui/position_body_gui.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "atrias_gui");	
	ros::NodeHandle n;	
	simulation_client = n.serviceClient<drl_plugins::position_body_srv>("/position_body_srv");
	simulation_srv.request.hold_robot 						 = true;
	simulation_srv.request.pause_simulation 			 = false;
	simulation_srv.request.desired_pose.position.x = 0.;
	simulation_srv.request.desired_pose.position.y = 0.;
	simulation_srv.request.desired_pose.position.z = 1.;

	Gtk::Main gtk(argc, argv);

	// Create the relative path to the Glade file.
	std::string glade_gui_path = std::string(argv[0]);
	
	glade_gui_path = glade_gui_path.substr(0, glade_gui_path.rfind("/bin"));
	glade_gui_path = glade_gui_path.append("/src/position_body_gui.glade");

	Glib::RefPtr<Gtk::Builder> gui = Gtk::Builder::create();
	try
	{
		gui->add_from_file(glade_gui_path);		
	}
	catch(const Glib::FileError& ex)
	{
		ROS_ERROR("File Error");
//			ROS_ERROR("FileError: %d", ex.what());
	}
	catch(const Gtk::BuilderError& ex)
	{
		ROS_ERROR("Builder Error");
//			ROS_ERROR("BuilderError: %d", ex.what());
	}

	// Grab pointers to GUI objects
	gui->get_widget("window", window);
	if(!window)
	{		
		ROS_ERROR("No GUI Window");
	}

	gui->get_widget("x_position_hscale", x_position_hscale);
	gui->get_widget("y_position_hscale", y_position_hscale);
	gui->get_widget("z_position_hscale", z_position_hscale);

	gui->get_widget("pause_button", pause_button);
	gui->get_widget("play_button", play_button);
	gui->get_widget("hold_button", hold_button);
	gui->get_widget("release_button", release_button);
	gui->get_widget("get_position_button", get_position_button);

	// Initialize GUI objects
	x_position_hscale->set_range(-100., 100.);
	y_position_hscale->set_range(-100., 100.);
	z_position_hscale->set_range(0.5, 1.5);
	
	z_position_hscale->set_value(1.0);

	// Wait for a maximum of 10000 ms simulation to come online.
	/*if (!ros::service::waitForService("/position_body_srv", 10000))
	{
		ROS_ERROR("No simulation detected.");
	}*/

	// Connect buttons to functions.
	pause_button->signal_clicked().connect( sigc::ptr_fun(pause_simulation) );
	play_button->signal_clicked().connect( sigc::ptr_fun(play_simulation) );
	hold_button->signal_clicked().connect( sigc::ptr_fun(hold_robot) );
	release_button->signal_clicked().connect( sigc::ptr_fun(release_robot) );
	get_position_button->signal_clicked().connect( sigc::ptr_fun(get_position) );

	x_position_hscale->signal_value_changed().connect( sigc::ptr_fun(desired_pose_changed) );
	y_position_hscale->signal_value_changed().connect( sigc::ptr_fun(desired_pose_changed) );
	z_position_hscale->signal_value_changed().connect( sigc::ptr_fun(desired_pose_changed) );

	gtk.run(*window);

  return 0;
}

void pause_simulation()
{
	simulation_srv.request.pause_simulation = true;
	while( !simulation_client.call(simulation_srv) );
}

void play_simulation()
{
	simulation_srv.request.pause_simulation = false;
	while( !simulation_client.call(simulation_srv) );
}

void hold_robot()
{
	simulation_srv.request.hold_robot = true;
	while( !simulation_client.call(simulation_srv) );
}

void release_robot()
{
	simulation_srv.request.hold_robot = false;
	while( !simulation_client.call(simulation_srv) );
}

void get_position()
{
	while( !simulation_client.call(simulation_srv) );
	desired_pose = simulation_srv.response.actual_pose;
	x_position_hscale->set_value(desired_pose.position.x);
	y_position_hscale->set_value(desired_pose.position.y);
	z_position_hscale->set_value(desired_pose.position.z);
}

void desired_pose_changed()
{
	simulation_srv.request.desired_pose.position.x = x_position_hscale->get_value();
	simulation_srv.request.desired_pose.position.y = y_position_hscale->get_value();
	simulation_srv.request.desired_pose.position.z = z_position_hscale->get_value();
	while( !simulation_client.call(simulation_srv) );
}
