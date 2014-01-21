import glob
import re
import os
import numpy
from matplotlib import pyplot
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

        self.res = {}

    def parse(self):
        for handle, name in zip(map(lambda x: open(x, 'r'), self._files), 
                           self._files):
            try:
                groups = self._regex.search(name).groupdict()
            except AttributeError:
                print("no match for ", name)
                continue
            

            to_add = [float(x.strip()) for x in handle]

            if groups['series'] not in self.res:
                self.res[groups['series']] = {}
            if groups['size'] not in self.res[groups['series']]:
                self.res[groups['series']][groups['size']] = {}
            if groups['threads']:
                self.res[groups['series']][groups['size']][groups['threads']] = to_add
            else: 
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
        
    def _par_overhead(self, size, thds):
        mean_par = numpy.mean(self.res['par'][size][thds])
        mean_ser = numpy.mean(self.res['serial'][size])
        return mean_ser / mean_par 


    def _get_dataseries(self, overhead): 
        return list(zip(*sorted(overhead.items(), key=lambda x:int(x[0]))))       

    def parallel_overhead(self):
        overhead = {}
        print([size for size in self.res['par']])
        for size in self.res['par'].keys():
            overhead[size] = self._par_overhead(size, '1')


        print(list(zip(*sorted(overhead.items(), key=lambda x:int(x[0])))))
        x, y = self._get_dataseries(overhead)
        pyplot.plot(x, y, 'bo-')
        pyplot.xlabel("Input Graph Size")
        pyplot.ylabel("Ratio of Serial to Parallel Execution Time")
        pyplot.legend(fancybox=True)
        pyplot.grid(True)
        pyplot.axis([0, 1045, 0, .6,])
        pyplot.show()


        print(overhead)

    def parallel_speedup(self):
        speedup = {}
        pyplot.hold(True)
        # thds = speedup['par']['16'].keys()
        # for thd in thds:
        #     speedup[thds] = {}
        #     for size in self.res['par']:
        #         speedup[thds][size] = self._par_overhead(size, thds)
        for size in self.res['par']:
            speedup[size] = {}
            for thds in self.res['par'][size]:
                speedup[size][thds] = self._par_overhead(size, thds)

        for size, color in sorted(zip(speedup, 'bgrcmyk'), key=lambda x:int(x[0])):
            x, y = self._get_dataseries(speedup[size])
            print(x)
            print(y)
            pyplot.plot(x, y, '{}o-'.format(color), label="{} nodes".format(size))


        pyplot.xlabel("Number of threads")
        pyplot.ylabel("Ratio of Serial to Parallel Execution Time")
        pyplot.legend(fancybox=True)
        pyplot.grid(True)
        pyplot.axis([0, 65, 0, 4.15,])
        pyplot.show()
        


def main(path):
    parser = ResultParser(path)
    parser.parse()
    print(parser.res)
    # parser.print_table()
    parser.parallel_overhead()
    # parser.parallel_speedup()

if __name__ == '__main__':
    main(argv[1])
