import os
files=os.listdir()
with open ('hej.txt','w') as fp:
    for item in files:
        if item.endswith(".obj"):
            fp.write("%s\n" % item)
    print('Done')