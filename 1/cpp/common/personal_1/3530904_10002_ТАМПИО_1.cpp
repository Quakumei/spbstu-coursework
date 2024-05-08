#include <iostream>

int main(){
    setlocale(LC_ALL, "Russian");
    std::cout << "������� ������������������ (����� ������������������ - 0):\n";

    int inputNum = 1;
    int seqLen = 0;
    std::cin >> inputNum;
    if (!std::cin || inputNum == 0) {
        std::cerr << "������������ ����, ���������� ���������...\n";
        return 1;
    }
    ++seqLen;
    int prevNum = 0;
    int numDiff = 0;
    int maxSeqDescendingLen = 0;
    int curSeqDescendingLen = 0;
    while (true) {
        prevNum = inputNum;
        std::cin >> inputNum;
        if(!std::cin){
            std::cerr << "������������ ����, ���������� ���������...\n";
            return 1;
        } else if (inputNum == 0){
            break;
        }
        ++seqLen;

        numDiff = inputNum - prevNum;
        if (numDiff >= 0){
            curSeqDescendingLen = 0;
        }
        else{
            ++curSeqDescendingLen;
            if (curSeqDescendingLen > maxSeqDescendingLen){
                maxSeqDescendingLen = curSeqDescendingLen;
            }
        }
    }

    if (seqLen == 1){
        std::cerr << "���������� ���������� ������������ ������������������, ��������� �� ������ ��������, ���������� ����������\n";
        return 1;
    } else if (maxSeqDescendingLen == 0){
        std::cout << "�������� ������������ � �������� ������������������ ���\n";
    } else {
        std::cout << "����� ����������� ���������� ��������� ������������������ - " << maxSeqDescendingLen + 1 << "\n";
    }
    return 0;
}
