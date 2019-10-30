#!/usr/bin/env python3.7


"""
Digital sound synthesizer with linear ADSR profile.
"""

import os
import re
import sys


def main():
    """"""

    colorers = [f"v{i}" for i in range(9)] + ['Min']
    colors = {colorer: 0 for colorer in colorers}
    elapsed = {colorer: 0 for colorer in colorers}
    turns = 0


    data = sys.stdin.read()
    regex = r'G\(V=(?P<V>\d+),\s+A=(?P<A>\d+).*?\n(?:.*?\n){3}' + \
            ''.join(f"\s+{colorer}\s+(?P<{colorer}_c>\d+)"
                                f"\s+(?P<{colorer}_t>\d+\.\d+).*?\\n" 
                    for colorer in colorers)
    

    for group in re.finditer(regex, data):
        group = group.groupdict()
        turns += 1

        for colorer in colorers:
            colors[colorer] += (int(group[colorer+'_c'])-int(group['Min_c']))
                              #  /int(group['V'])
            elapsed[colorer] += float(group[colorer+'_t'])\
                                /(int(group['V'])+int(group['A']))

    colors  = {colorer: colors[colorer]/turns 
               for colorer in colorers}
    elapsed = {colorer: elapsed[colorer]/turns 
               for colorer in colorers}

    print('total:', 
          turns)
    print('colors:', 
          *[f'{key}\t{value:.16f}' 
            for key, value in colors.items()], 
          sep='\n')
    print('elapsed:', 
          *[f'{key}\t{value:.16f}' 
            for key, value in elapsed.items()], 
          sep='\n')


if __name__ == '__main__':
    main()
