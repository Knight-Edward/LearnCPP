/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        if(!root) {
            return ret;
        }
        queue<TreeNode*> que;
        que.push(root);    // start
        while(!que.empty()) {
            int width = que.size();
            vector<int> temp;
            for(int i = 0; i < width; i++){
                TreeNode* front = que.front();
                if(front)
                    temp.push_back(front->val);
                // before pop out the front in the que, we push the children of it into the que
                if(front->left)
                    que.push(front->left);
                if(front->right)
                    que.push(front->right);
                que.pop();
            }
            ret.push_back(temp);
        }
        return ret;
    }
};
