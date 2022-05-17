/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <queue>
 #include <string.h>
 #include "treeStruct.h"
 #include "BSTPrinter.h"

 using namespace std;


class BSTOperator {
public:

    typedef void (*treeNodeCallback)(TreeNode* root);

    treeNodeCallback operation;

    #define doSomething(x) {if(operation != NULL) operation(x);}

    static void print(TreeNode* root) {
        if (root != NULL )
            printf("%d, ", root->val);
        else
            printf("NULL, ");
    }
    
    void printTree(TreeNode* root) {
        operation = print;
        bfs(root);
        printf("\r\n");
    }
    
    void bfs(TreeNode* root) {
        queue<TreeNode*> q;
        
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            doSomething(node);
            
            if (node != NULL) {
                q.push(node->left);
                q.push(node->right);
            }
        }
    }

    void inorder(TreeNode* root) {
        if (root == NULL)
            return;

        inorder(root->left);
        doSomething(root);
        inorder(root->right);
    }
    void preorder(TreeNode* root) {
        if (root == NULL)
            return;

        doSomething(root);
        preorder(root->left);        
        preorder(root->right);
    }
    void postorder(TreeNode* root) {
        if (root == NULL)
            return;
        
        postorder(root->left);        
        postorder(root->right);
        doSomething(root);
    }    
    
    void insertNode(TreeNode* root, int val) {
        insertNode(root, new TreeNode(val));
    }

    void insertNode(TreeNode* root, TreeNode* node) {
        if (node->val < root->val) {                // 比較小，往左子樹放
            if (root->left != NULL) {
                insertNode(root->left, node);    // 左節點非空，往左子樹找位置
            }
            else {
                root->left = node;                  // 左節點為空，直接成為左節點
            }
        }
        else if (node->val > root->val) {           // 比較大，往右子樹放
            if (root->right != NULL) {
                insertNode(root->right, node);   // 右節點非空，往右子樹找位置
            }
            else {
                root->right = node;                 // 右節點為空，直接成為右節點
            }            
        }
        else {
            ; // 如果值相等，則不新增節點，什麼都不做
        }
    }

   TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL)
            return root;
        
        TreeNode* tempR = root->right;
        TreeNode* tempL = root->left;        
        
        if (root->val == key) {
            if (root->left == NULL && root->right != NULL) {                
                root->right = NULL;
                return tempR;
            }
            else if (root->left != NULL && root->right == NULL) {
                root->left = NULL;
                return tempL;
            }
            else if (root->left != NULL && root->right != NULL) {
                // todo: return the successor
                TreeNode* successor = NULL;
                
                if (root->right->left == NULL) {
                    // The right side maybe the successor itself sometimes
                    successor = root->right;                
                }
                else {
                    TreeNode* successorFather = findSuccessorFather(tempR);
                    successor = successorFather->left;
                    successorFather->left = successor->right;                    
                }
                
                root->left = NULL;
                root->right = NULL;
                
                successor->left = tempL;
                
                if (tempR != successor)
                    successor->right = tempR;                
                                
                return successor;
            }
            else {
                return NULL;
            }            
        }
        
        if (root->left != NULL) {
            root->left = deleteNode(root->left, key);
        }
        if (root->right != NULL) {
            root->right = deleteNode(root->right, key);   
        }            
        return root;
    }
    
    TreeNode* findSuccessorFather(TreeNode* root) {                        
        if (root->left->left == NULL) {
            return root;
        }        
        return findSuccessorFather(root->left);
    }
};

int main()
{
    BSTOperator bst;
    
    TreeNode* root = new TreeNode(50);
        
    bst.insertNode(root, 80);  
    bst.insertNode(root, 30);
    bst.insertNode(root, 45);
    bst.insertNode(root, 93);           
    
    bst.insertNode(root, 62);
    
    bst.insertNode(root, 22);
    bst.insertNode(root, 70);  
    bst.insertNode(root, 48);
          
    bst.insertNode(root, 40);
    bst.insertNode(root, 42);     
    

    bst.operation = bst.print;
    
    printf("BFS:       "); bst.bfs(root);       printf("\n");
    printf("Inorder:   "); bst.inorder(root);   printf("\n");
    printf("Preorder:  "); bst.preorder(root);  printf("\n");
    printf("Postorder: "); bst.postorder(root); printf("\n");


    BSTPrinter printer;
    printf("\r\n[Tree Visualization]\r\n\n\n\n");
    printer.doShowBSTree(root);
    /*    
    root = bst.deleteNode(root, 80);
    root = bst.deleteNode(root, 30);

    printf("\r\n[Tree Visualization]\r\n\n\n\n");
    printer.doShowBSTree(root);*/

    return 0;
}

