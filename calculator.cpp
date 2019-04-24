#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class digit
{
    public:
    int data;
    digit *next = nullptr;
};

char getOperator(ifstream &file)
{
  char op;
  string endLine;
  file.get(op);
  getline(file, endLine);
  return op;
}

void writeNumber(digit *num, ofstream &file)
{
  while(num != nullptr)
  {
    file << num->data;
    num = num->next;
  }
  file << endl;
  return;
}

digit *deleteNumber(digit *num)
{
  digit *dig;
  dig = num->next;
  delete num;
  num = dig;
  return dig;
}

digit *addNumbers(digit *left, digit *right)
{
  digit *total = new digit;
  digit *tTemp = total;
  int num, carryOver = 0;
  while(left != nullptr && right != nullptr)
  {
    num = left->data + right->data;
    //cout << "Num is " << num << endl;
    if(num > 9)
    {
      num = num - 10;
      total->data = num + carryOver;
      carryOver = 1;
    }
    else
    {
      total->data = num + carryOver;
      carryOver = 0;
    }
    //cout << total->data;
    left = left->next;
    right = right->next;
    if(left != nullptr && right != nullptr)
    {
      tTemp = total;
      total = new digit;
      total->next = tTemp;
    }
    else
      break;
  }
  return total;
}
/*
digit *subNumbers(digit *left, digit *right)
{
  digit theDigit;
  return theDigit;
}*/

digit *loadNumber(ifstream &numFile)
{
  if(numFile.eof())
    return nullptr;
  digit *head = new digit;
  digit *temp = head;

  char dig;
  int num;
  numFile.get(dig);
  while(!numFile.eof() || dig != '\n')
  {
    num = int(dig - '0');
    head->data = num;
    numFile.get(dig);
    if(dig != '\n')
    {
      temp = head;
      head = new digit;
      head->next = temp;
    }
    else
      break;
  }
  return head;
}

int main()
{
  ifstream numFile;
  ofstream outFile;
  char op;
  digit *left, *right, *total;
  numFile.open("largeNumbers.txt");
  while (!numFile.eof())
  {
    left = loadNumber(numFile);
    right = loadNumber(numFile);
    op = getOperator(numFile);
    if(op == '+')
      total = addNumbers(left,right);
      /*while(total != nullptr)
      {
        cout << total->data;
        total = total->next;
      }*/
    break;
  }
  outFile.open("output.txt");
  writeNumber(total, outFile);
  outFile.close();
  numFile.close();

  return 0;
}
