single_type = 0x00
alt_type = 0x01
ctrl_type = 0x02
shift_type = 0x04
a_c_type = bor(alt_type,ctrl_type)
a_s_type = bor(alt_type,shift_type)
s_c_type = bor(ctrl_type,shift_type)
a_c_s_type = bor(a_c_type,shift_type)