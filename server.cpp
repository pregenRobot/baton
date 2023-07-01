

#include <iostream>
#include <torch/torch.h>

using namespace std;
using namespace torch;
int main(int argc, char** argv){
    torch::Tensor tensor = torch::rand({2,3});
    cout << "Started Server" << endl;
}
