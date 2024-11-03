# -*- encoding:UTF-8 -*-
import os
import json

# 向上移动两级目录
postgresql_project = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

print(postgresql_project + '\n')

postgres_pid = os.popen('pgrep /media/skylinux/sky_code/postgresql-17.0/build/bin/postgres -f')
pg_id = []
for pid in postgres_pid.readlines() :
    pg_id.append(pid.partition("\n")[0])

with open(postgresql_project + '/.vscode/launch.json','r',encoding='utf8') as launch_read:
    launch_data = json.load(launch_read)
    for configurations_data in launch_data['configurations'] :
        if configurations_data['name'] == 'postgres data1 attach' :
            configurations_data['processId'] = pg_id[0]


with open(postgresql_project + '/.vscode/launch.json','w',encoding='utf8') as launch_write:
    json.dump(launch_data, launch_write, sort_keys=False, indent=4, separators=(', ', ': '), ensure_ascii=False)

print('attach pid config success.')