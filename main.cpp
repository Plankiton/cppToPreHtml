#include <iostream>
#include <fstream>
using namespace std;

void help();
string to_html(string line);
bool parse_cli(int argc, char ** argv);

bool use_stdout = false;
string name, filename, out_filename;
int main(int argc, char ** argv)
{
  name = argv[0];

  if (!parse_cli(argc, argv))
    return 1;

  cout << filename << endl;

  ifstream in_file(filename);

  // If error on opening file show message error and show help message
  if (!in_file.is_open())
  {
    cerr << name << ": Error opening file, verify if then exists" << endl;
    help();
    return 1;
  }

  ofstream out_file(out_filename);
  if (!out_file.is_open())
    use_stdout = true;

  string line = "<pre>";

  if (use_stdout) {
    cout << line << endl;
  } else {
    out_file << line << endl;
  }

  while (getline(in_file, line)) {
    line = to_html(line);
    if (use_stdout) {
      cout << line << endl;
    } else {
      out_file << line << endl;
    }
  }

  line = "</pre>";
  if (use_stdout) {
    cout << line << endl;
  } else {
    out_file << line << endl;
  }

  in_file.close();
  out_file.close();
  return 0;
}

void help()
{
  cout <<
    name << " <file>.cpp [OPTIONS]" << endl
    << endl
    << "OPTIONS" << endl
    << "-------------------" << endl
    << "-h           Show this message" << endl
    << "-o <output>  Set output to HTML text" << endl
    << "             if empty, text will to stdout" << endl
    << endl;
}

bool parse_cli(int argc, char ** argv)
{
  // If not arguments on command line show help message
  if (argc <= 1)
  {
    help();
    return false;
  }

  for (int i = 1; i < argc; i++)
  {
    if (out_filename != "") {
      continue;
    }

    if (argv[i][0] == '-')
    {
      if (argv[i][1] == 'o')
        out_filename = argv[i+1];
      if (argv[i][1] == 'h')
      {
        help();
        return false;
      }
    } else
    {
      filename = argv[i];
    }
  }

  return true;
}

string to_html(string line) {
  return line;
}
