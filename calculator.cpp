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
/*
digit *loadNumber(ifstream &file)
{
  digit theDigit;
  return theDigit;
}
*/
char getOperator(ifstream &file)
{
  char op;
  string endLine;
  file.get(op);
  getline(file, endLine);
  return op;
}
/*
void writeNumber(digit *num, ofstream &file)
{

  return;
}
*/
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
  //digit *ltemp = new digit;
  //digit *rtemp = new digit;
  int num;
  while(left != nullptr || right != nullptr)
  {
    num = left->data + right->data;
    cout << left->next->data;
    cout << "Num is " << num;
    //total->data = num;
    //cout << total->data;
    //left = left->next;
    //right = right->next;
    //num = left->data + right->data;
    left = deleteNumber(left);
    right = deleteNumber(right);
    cout << "Num is " << num;
    break;
    //deleteNumber(left);
    //deleteNumber(right);
  }
  return total;
}
/*
digit *subNumbers(digit *left, digit *right)
{
  digit theDigit;
  return theDigit;
}*/

digit *inputNum(ifstream &numFile)
{
  if(numFile.eof())
    return nullptr;
  digit *head = new digit;
  digit *temp = head;
  char dig;
  int num;
  while(!numFile.eof())
  {
    numFile.get(dig);
    if (dig == '\n')
      break;
    num = int(dig - '0');
    //cout << num << endl;
    head->data = num;
    temp = head;
    head->next = temp;
  }
  return head;
}

int main()
{
  ifstream numFile;
  //ofstream outFile;
  char op;
  digit *left, *right, *total;
  //cout << left->data;
  numFile.open("largeNumbers.txt");
  while (!numFile.eof())
  {
    left = inputNum(numFile);
    right = inputNum(numFile);
    op = getOperator(numFile);
    if(op == '+')
      total = addNumbers(left,right);

    break;
    //numFile.get(dig);
    //cout <<  dig;
  }
  //outFile.open("output.txt");

  return 0;
}
