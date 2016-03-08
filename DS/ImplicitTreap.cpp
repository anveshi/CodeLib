class ImplicitTreap {

    public:

    struct Node {
      int priority, size, reverse, value, sum, lazy;
      Node * left, * right;
      Node(int value) : value(value), priority(rand()) {
        size = 1;
        lazy = 0;
        left = right = NULL;
        sum = value;
      }
      void doReverse() {
        reverse = 1 - reverse;
        swap(left, right);
      }
    };
   
    /* Usage of split */
    /*
          split(A, B, C, value) splits the tree
          such that indexes 0 to value - 1 are
          contained in B (also size of B is value)
          and C contains all other elements. 
     */

    void insert(int position, int c) {
      Node * left, * right;
      split(head, left, right, position);
      head = merge(merge(left, new Node(c)), right);
      return;
    }

    int getsum(int l, int r) {
      Node * a, * b, * c, * d;
      split(head, a, b, l);
      split(b, c, d, r - l + 1);
      assert(c != NULL);
      int ans = c->sum;
      head = merge(merge(a, c), d);
      return ans;
    }
    
    void reverse(int l, int r) {
      Node * a, * b, * c, * d;
      split(head, a, b, l);
      split(b, c, d, r - l + 1);
      c->doReverse();
      head = merge(merge(a, c), d);
    }

    void transferSegmentToStart(int l, int r) {
      Node * a, * b, * c, * d;
      split(head, a, b, l);
      split(b, c, d, r - l + 1);
      head = merge(merge(c, a), d);
    }
    
    void update(int l, int r, int value) {
      Node * a, * b, * c, * d;
      split(head, a, b, l); // indexes 0 to l - 1 go in left others in right...
      split(b, c, d, r - l + 1);
      c->lazy = value;
      head = merge(merge(a, c), d);
    }

    void printTreap() {
      data.clear();
      print(head);
      for(int i = 0; i < data.size(); i++) {
        cout << i << "-" << data[i] << "  ";
      }
      cout << endl;
    }

    ImplicitTreap() {
      head = NULL;
    }

    private:

    Node * head;
    vector<int> data; // used for debugging in printTreap() method.

    int getSize(Node * root) {
      return (root == NULL) ? 0 : root->size;
    }

    void updateSize(Node * root) {
      if(root) root->size = getSize(root->left) + getSize(root->right) + 1;
    }

    void pushDown(Node * root) {
      if(!root) return;

      if(root->reverse) {
        if(root->left) root->left->doReverse();
        if(root->right) root->right->doReverse();
        root->reverse = 0;
      }

      if(root->lazy) {
        root->value += root->lazy;
        root->sum += (getSize(root) * root->lazy);
        if(root->left) root->left->lazy += root->lazy;
        if(root->right) root->right->lazy += root->lazy;
        root->lazy = 0;
      }
    }

    void reset(Node * root) {
      if(root) {
        root->sum = root->value;
      }
    }

    void combine(Node * & root, Node * left, Node * right) {
      if(left == NULL || right == NULL) {
        root = left ? left : right;
        return;
      }
      root->sum = left->sum + right->sum;
    }

    void operation(Node * root){
      if(root == NULL) return;
      reset(root);
      pushDown(root->left);
      pushDown(root->right);
      combine(root, root->left, root);
      combine(root, root, root->right);
    }

    void split(Node * root, Node * & left, Node * & right, int splitAbout, int addOffset = 0) {
      if(root == NULL) {
        left = right = NULL;
        return;
      }

      pushDown(root);

      int currentKey = addOffset + getSize(root->left);
      if(currentKey < splitAbout) {
        split(root->right, root->right, right, splitAbout, currentKey + 1);
        left = root;
      } else {
        split(root->left, left, root->left, splitAbout, addOffset);
        right = root;
      }

      updateSize(root);
      operation(root);
    }

    Node * merge(Node * left, Node * right) {
      if(left == NULL || right == NULL) return left ? left : right;
      pushDown(left);
      pushDown(right);
      if(left->priority > right->priority) {
        left->right = merge(left->right, right);
        updateSize(left);
        operation(left);
        return left;
      } else {
        right->left = merge(left, right->left);
        updateSize(right);
        operation(right);
        return right;
      }
    }

    void print(Node * root) {
      if(root == NULL) return;
      operation(root);
      print(root->left);
      data.push_back(root->value);
      print(root->right);
    }

};