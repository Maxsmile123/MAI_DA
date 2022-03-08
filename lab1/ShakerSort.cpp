#include "ShakerSort.h"

void TShakerSort::swap(TElement *a, TElement *b){
    TElement c = *a;
    *a = *b;
    *b = c;
}

std::vector<TElement> TShakerSort::sort(std::vector<TElement>& data){
    if (data.size() <= 1){
        return data;
    }
    bool flag = true;
    int beginIndex = -1;
    int endIndex = data.size() - 1;
    while(flag){
        flag = false;
        beginIndex++;
        for (int i = beginIndex; i < endIndex; ++i){
            if(data[i].key > data[i + 1].key){
                swap(&data[i], &data[i + 1]);
                flag = true;
            }
        }
        if (!flag) break;
        endIndex--;
        for (int i = endIndex; i > beginIndex; --i){
            if(data[i].key < data[i - 1].key){
                swap(&data[i], &data[i - 1]);
                flag = true;
            }
        }

    }
    return data;


}