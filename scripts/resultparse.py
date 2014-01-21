import glob
import re
import os


class ResultParser:
    def __init__(self, base_dir, ext='txt', groupnames=['series', 'size', 'threads']):
        PATTERN = r'(P<{}>\w+)-(P<{}>\d+)-(P<{}>\d+)?'.format(*groupnames)

        self._groupnames = groupnames
        self._regex = re.compile(pattern)
        self._files = glob.glob(os.path.join(base_dir, ext))

        self.res = {}

        


    def parse(self):
        for handle, name in zip(map(lambda x: open(x, 'r'), self._files), 
                           self._files):
            groups = self._regex.match(name).groups

            to_add = [int(x.strip()) for x in 
            
            if groups[0] not in self.res.keys():
                self.res[groups[0]] = {}
            if groups[1] not in self.res[groups[0]].keys():
                self.res[groups[0]][groups[1]] = {}


            self.res[self_groupnames[0]][self._groupnames[1]]
                
                
        
        
