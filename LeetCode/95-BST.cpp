#include <iostream>
#include <vector>
//Definition for a binary tree node.
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    vector<TreeNode*> generateResults(int start, int end) {
        vector<TreeNode*> allTrees;
        if(start > end){
            TreeNode* temp = NULL;
            allTrees.push_back(temp);
        }
        // 枚举可行根节点
        for (int i = start; i <= end; i++) {
            // 获得所有可行的左子树集合
            vector<TreeNode*> leftTrees = generateResults(start, i - 1);

            // 获得所有可行的右子树集合
            vector<TreeNode*> rightTrees = generateResults(i + 1, end);

            // 从左子树集合中选出一棵左子树，从右子树集合中选出一棵右子树，拼接到根节点上
            for (auto& left : leftTrees) {
                for (auto& right : rightTrees) {
                    TreeNode* currTree = new TreeNode(i);
                    currTree->left = left;
                    currTree->right = right;
                    allTrees.push_back(currTree);
                }
            }
        }
        return allTrees;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ret;
        //TreeNode *temp = new TreeNode(1);
        //ret.push_back(temp);
        if(!n) {
            return ret;
        }
        ret = generateResults(1, n);
        return ret;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    Solution solu;
    vector<TreeNode*> ret = solu.generateTrees(3);
    for(int i=0; i<ret.size();i++){
        cout << ret[i]->val << endl;
    }
    return 0;
}

