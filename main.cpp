#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <unordered_map>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<int,int> & pr) {
        os << "(" << pr.first << "," << pr.second << ")";
        return os;
    }
}

// class solution {
//   public:
//     std::vector<std::vector<std::pair<int,int>>> takeCandies(int n) {
//         std::vector<std::vector<std::pair<int,int>>> paths;
//         std::vector<std::pair<int,int>> next = getNext(n);
//         for (auto nx : next) {
//             auto temp = takeCandies(n-nx.first-nx.second);
//             if (temp.empty()) {
//                 if (nx.first == 1 && nx.second == 0)
//                     paths.push_back(std::vector<std::pair<int,int>>{nx});
//             }
//             else {
//                 for (auto tmp : temp) {
//                     if (tmp.back().first == 1 && tmp.back().second == 0) {
//                         tmp.insert(tmp.begin(), nx);
//                         paths.push_back(tmp);
//                     }
//                 }
//             }
//         }

//         // std::for_each(paths.begin(), paths.end(),
//         //               [](const std::vector<std::pair<int,int>> & vec){
//         //                   if (vec.back().second != 0) {
//         //                       std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
//         //                       std::cout << std::endl;
//         //                   }
//         //               });
//         return paths;
//     }

//   private:
//     std::vector<std::pair<int,int>> getNext(int n) {
//         std::vector<std::pair<int,int>> next;
//         if (n > 0) {
//             for (int i = 1; i <= 4; i++) {
//                 if (n-i == 0)
//                     next.push_back(std::make_pair(i,n-i));
//                 else {
//                     for (int j = 1; j <= std::min(4, n-i); j++)
//                         next.push_back(std::make_pair(i,j));
//                 }
//             }
//         }
//         return next;
//     }
// };

// int main() {
//     int numCandies = 6;

//     solution soln;
//     auto wins = soln.takeCandies(numCandies);
//     std::for_each(wins.begin(), wins.end(),
//                   [](const std::vector<std::pair<int,int>> & vec){
//                       // if (vec.front().first == 1 && vec.front().second == 1) { 
//                           std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
//                           std::cout << std::endl;
//                       // }
//                   });
// }


class solution {
  public:
    solution(int mn, int mx) : min(mn), max(mx){}
    
    std::vector<std::pair<int,int>> takeCandies(int numCandies) {
        srand(time(NULL));
        std::vector<std::pair<int,int>> result;
        int num = numCandies;
        int take1, take2;
        while (num > 0) {
            if (winIfLeftWith(num, take1)) {
                if (num == numCandies)
                    std::cout << "First wins! ";
                if (!winIfLeftWith(num-take1, take2)) {
                    if (num-take1 == 1)
                        take2 = 1;
                    else {
                        take2 = int(rand())%max+1;
                    }
                }
            }
            else {
                if (num == numCandies)
                    std::cout << "Second wins! ";
                if (num == 1)
                    take1 = 1;
                else
                    take1 = int(rand())%max+1;
                winIfLeftWith(num-take1, take2);                
            }
            
            result.push_back(std::make_pair(take1,take2));
            num -= (take1+take2);
        }

        std::copy(result.begin(), result.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, ""));
        std::cout << std::endl;

        return result;
    }

  private:
    bool winIfLeftWith(int n, int & take) {
        // if (n == 0) {
        //     if (computed.find(n) == computed.end())
        //         computed[n] = true;
        //     if (dict.find(n) == dict.end())
        //         dict[n] = 0;
        //     take = dict[n];
        //     return computed[n];
        // }
        // else if (n == 1) {
        //     if (computed.find(n) == computed.end())
        //         computed[n] = false;
        //     return computed[n];
        // }
        // else if ( n > min && n <= min+max) {
        //     if (computed.find(n) == computed.end())
        //         computed[n] = true;
        //     if (dict.find(n) == dict.end())
        //         dict[n] = n-1;
        //     take = dict[n];
        //     return computed[n];
        // }
        // else {
        //     for (int i = min; i <= max; i++) {
        //         if (!winIfLeftWith(n-i, take)) {
        //             if (computed.find(n) == computed.end())
        //                 computed[n] = true;
        //             if (dict.find(n) == dict.end())
        //                 dict[n] = i;
        //             take = dict[n];
        //             return computed[n];
        //         }
        //     }
        //     if (computed.find(n) == computed.end())
        //         computed[n] = false;
        //     return computed[n];
        // }

        if (n == 0) {
            take = 0;
            return true;
        }
        else {
            if (n%(min+max) == 1) {
                return false;
            }
            else {
                take = min;
                while (take < max && (n-take)%(min+max) != 1)
                    take++;
                return true;
            }
        }
    }

    // std::unordered_map<int,bool> computed;
    // std::unordered_map<int,int> dict;
    int min, max;
};

int main() {
    int numCandies = 20;
    int mintake = 1, maxtake = 3;

    solution soln(mintake, maxtake);
    auto path = soln.takeCandies(numCandies);
    
}
