import re
from pathlib import Path
base = Path('AntennaTracker')
header = (base / 'Parameters.h').read_text()
cpp = (base / 'Parameters.cpp').read_text()
enum = re.findall(r'k_param_([A-Za-z0-9_]+)', header)
vars = re.findall(r'AP_[A-Za-z0-9_]+\s+([A-Za-z0-9_]+);', header)
info = re.findall(r'GSCALAR\(([A-Za-z0-9_]+),|GOBJECT\(([A-Za-z0-9_]+),|GGROUP\(([A-Za-z0-9_]+),', cpp)
info_names = [x[0] or x[1] or x[2] for x in info]
missing_enum = sorted({name for name in info_names if name not in enum})
missing_var = sorted({name for name in info_names if name not in vars})
print('missing_enum=' + ','.join(missing_enum))
print('missing_var=' + ','.join(missing_var))
extra_enum = sorted({name for name in enum if name not in info_names and name not in ['format_version','software_type','gcs0_unused','gcs1_unused','sysid_this_mav_old','sysid_my_gcs_old','serial0_baud','serial1_baud','imu','compass_enabled_deprecated','compass','ahrs','barometer','scheduler','ins','sitl','pidPitch_old','pidYaw_old','gcs2_unused','serial2_baud','BoardConfig','gps','notify','can_mgr','gcs3_unused','log_bitmask','gcs4_unused','gcs5_unused','gcs6_unused','channel_yaw_old','channel_pitch_old','pidPitch2Srv','pidYaw2Srv','rc_channels','servo_channels','stats_old','scripting_old','command_total','gcs_pid_mask','scan_speed_yaw','scan_speed_pitch','initial_mode','disarm_pwm','auto_opts','NavEKF2','NavEKF3','logger','vehicle','_gcs']})
print('extra_enum=' + ','.join(extra_enum))
print('enum_count=' + str(len(enum)))
print('var_count=' + str(len(vars)))
print('info_count=' + str(len(info_names)))
