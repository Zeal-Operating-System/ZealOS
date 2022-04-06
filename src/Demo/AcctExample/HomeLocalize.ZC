//Place this file in /Home and change
//anything you want.

Option(OPTf_WARN_PAREN, ON);
Option(OPTf_WARN_DUP_TYPES, ON);

KbdTypeMatic(0);

// Las Vegas is -7 during summer, -8 during winter
local_time_offset = -7 * 60 * 60 * CDATE_FREQ; //Pacific
// Remember you can set the time in the BIOS.

//$AN,"",A="mouse_move_scale"$adjust these to set mouse move scale
mouse_hard.scale.x = 0.5;
mouse_hard.scale.y = 0.5;
mouse_hard.scale.z = 5.0; //wheel

//don't change these
mouse_hard.prescale.x = mouse_hard.pos.x / mouse_hard.scale.x;
mouse_hard.prescale.y = mouse_hard.pos.y / mouse_hard.scale.y;
mouse_hard.prescale.z = mouse_hard.pos.z / mouse_hard.scale.z;
