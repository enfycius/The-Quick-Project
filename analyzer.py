import os
import sys
import json
import shutil

try:
    thres = float(sys.argv[1])
    class_menu = int(sys.argv[2])
except:
    print("Not Float Arguments")
    sys.exit()

if len(sys.argv) != 3:
    print("Insufficient arguments")
    sys.exit()

ori = 'C:/darknet/data/import'

with open("C:/darknet/result.json", "r") as f:
    j_data = json.load(f)

    for i, j in enumerate(j_data):
        inner_objects = j_data[i]["objects"]
        file_path = j_data[i]["filename"].split('/')

        if not os.path.isdir(ori + '/' + 'want'):
            os.makedirs(ori + '/' + 'want')
        
        if not os.path.isdir(ori + '/' + 'need_check'):
            os.makedirs(ori + '/' + 'need_check')

        try:
            inner_objects[0]["class_id"]

            for k, m in enumerate(inner_objects):
                if inner_objects[k]["confidence"] >= thres and inner_objects[k]["class_id"] == class_menu:
                    file_path.insert(-1, 'want')
                    edit_file_path = '/'.join(file_path)
                    
                    try:
                        shutil.move(j_data[i]["filename"], edit_file_path)
                    except:
                        pass
                else:
                    file_path.insert(-1, 'need_check')
                    edit_file_path = '/'.join(file_path)

                    try:
                        shutil.move(j_data[i]["filename"], edit_file_path)
                    except:
                        pass

        except:
            file_path.insert(-1, 'need_check')
            edit_file_path = '/'.join(file_path)

            try:
                shutil.move(j_data[i]["filename"], edit_file_path)
            except:
                pass