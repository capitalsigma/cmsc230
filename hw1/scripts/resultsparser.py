import glob
import re
import os
import numpy
from sys import argv


class ResultParser:
    def __init__(self, base_dir, ext='txt'):
        groupnames = ['series', 'size', 'threads']

        PATTERN = \
            r'(?P<{}>\w+)-(?P<{}>\d+)(-(?P<{}>\d+))?.txt'.format(*groupnames)

        self._groupnames = groupnames
        self._regex = re.compile(PATTERN)
        self._files = glob.glob(os.path.join(base_dir, "*.{}".format(ext)))
        print(os.path.join(base_dir, ext))
        print(self._files)

        self.res = {}

    def parse(self):
        for handle, name in zip(map(lambda x: open(x, 'r'), self._files), 
                           self._files):
            try:
                groups = self._regex.search(name).groupdict()
                print(groups)
            except AttributeError:
                print("no match for ", name)
                continue
            

            to_add = [float(x.strip()) for x in handle]

            if groups['series'] not in self.res:
                print('yes1')
                self.res[groups['series']] = {}
            if groups['size'] not in self.res[groups['series']]:
                print('yes2')
                self.res[groups['series']][groups['size']] = {}
            if groups['threads']:
                print('yes3')
                self.res[groups['series']][groups['size']][groups['threads']] = to_add
            else: 
                print('yes4')
                self.res[groups['series']][groups['size']] = to_add

        return self.res

    def _get_result(self, result_list):
        return "{:.4f} ({:.4f})".format(numpy.mean(result_list), 
                                        numpy.std(result_list))
        
    
    def _print_par_section(self, up_to, first):
        part = lambda x: x[:up_to] if first else x[up_to:]
        print("Size,{}".format(','.join(part(sorted(self.res['par']['16'], key=int)))))
        for size, thread_vals in sorted(self.res['par'].items(), 
                                        key=lambda x:int(x[0])):
            vals = part(sorted(thread_vals.items(), key=lambda x:int(x[0])))
            print(size, ',', ','.join([self._get_result(y[1]) for y in vals]), sep='')

    
    def print_table(self):
        print("serial: ")
        print("Size,Time")
        for key, value in sorted(self.res['serial'].items(), key=lambda x:int(x[0])):
            print("{},{}".format(key, self._get_result(value)))
        
        print("parallel: ")
        
        self._print_par_section(4, True)
        self._print_par_section(4, False)
        

    def make_graphs(self):
        pass


def main(path):
    parser = ResultParser(path)
    print(parser.parse())
    parser.print_table()

if __name__ == '__main__':
    try:
        main(argv[1])
    
