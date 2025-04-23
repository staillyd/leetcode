import os
from functools import reduce

if __name__ == "__main__":
    paths = __file__.split('/')
    format_path = reduce(lambda x, y: x + '/' + y, paths[:-1])
    filter_files = ["__init__.py", "__main__.py", "cmdline.py", "demo.py"]
    for dirpath, dirnames, filenames in os.walk(format_path):
        for file in filenames:
            if file[-3:] != '.py' or file in filter_files:  #or file[-6:] == 'pb2.py'
                continue
            os.system("yapf -i %s --style='{ based_on_style: google, indent_width: 4, column_limit: 120 }'" %
                      (os.path.join(dirpath, file)))
