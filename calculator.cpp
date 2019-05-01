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

void deleteNumber(digit *num)
{
  digit *dig;
  while (num != nullptr)
  {
    dig = num->next;
    delete num;
    num = dig;
  }
}

digit *addNumbers(digit *left, digit *right)
{
  digit *total = new digit;
  digit *tTemp = total;
  int num, carryOver = 0;
  while(left != nullptr && right != nullptr)
  {
    num = left->data + right->data;
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
    left = left->next;
    right = right->next;
    if(left != nullptr && right != nullptr)
    {
      tTemp = total;
      total = new digit;
      total->next = tTemp;
    }
    else if(left != nullptr && right == nullptr)
    {
      left = left->next;
      while(left != nullptr)
      {
        tTemp = total;
        total = new digit;
        total->next = tTemp;
        total->data = left->data;
        if(left->next == nullptr)
          break;
        left = left->next;
      }
    }
    else if(left == nullptr && right != nullptr)
    {
      right = right->next;
      while(right != nullptr)
      {
        tTemp = total;
        total = new digit;
        total->next = tTemp;
        total->data = right->data;
        if(right->next == nullptr)
          break;
        right = right->next;
      }
    }
  }
  return total;
}

digit *writeNumber(ifstream &numFile)
{
  if(numFile.eof())
    return nullptr;
  digit *head = new digit;
  digit *temp = head;

  char dig;
  string crap;
  int num;
  numFile.get(dig);
  num = int(dig - '0');
  while(!numFile.eof() || dig != '\n')
  {
    head->data = num;
    numFile.get(dig);
    if(dig != '\n')
    {
      num = int(dig - '0');
      if (num == -48)
        break;
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
  int i = 0;
  char op;
  string test;
  digit *left, *right, *total;
  numFile.open("largeNumbers.txt");
  outFile.open("output.txt");
  while (!numFile.eof())
  {
    left = writeNumber(numFile);
    right = writeNumber(numFile);
    if (left == nullptr || right == nullptr)
    {
      break;
    }
    op = getOperator(numFile);
    if(op == '+')
      total = addNumbers(left,right);
    writeNumber(total, outFile);
    deleteNumber(left);
    deleteNumber(right);
    deleteNumber(total);
    left = nullptr;
    right = nullptr;
    total = nullptr;
    i = i + 1;
    if(i == 5)
      break;
  }
  outFile.close();
  numFile.close();
  return 0;
}
