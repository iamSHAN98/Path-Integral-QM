import sys
import argparse

def get_arguments() :
  parser = argparse.ArgumentParser(description = "")
  parser.add_argument('-c', '--config', type = str, help = "Configuration file")
  parser.add_argument('-i', '--input', type = str, nargs = '*', help = "Input file(s)")
  parser.add_argument('-o', '--output', type = str, nargs = '*', help = "Plot(s), output file(s)")
  args = parser.parse_args()
  return args

def get_config(file_path) :
  config = {}
    
  with open(file_path, "r") as file :
    lines = file.read().splitlines() 

    for line in lines :
      if((line == '') or (line[0] == " ") or (line[0] == "\t")):          # Ignore blank lines
        continue
      if(line[0] == '#') :                                                # Ignore comments
        continue

      value = line.split()
      key, value = value[0], value[1:]                                    # Key-value pair

      if len(value) == 1 :
        config[key] = eval(value[0])
      else :
        config[key] = [eval(entry) for entry in value]

  return config


if __name__ == "__main__" :
  try :
    print(get_config(sys.argv[1]))
  except :
    print("Require path for configuration")