namespace matrix {

template <class T, int dim>
Matrix {
    public:
        Matrix (vector <vector <T> >);
        Matrix add (Matrix &otherMatrix);
        Matrix multiply (Matrix &otherMatrix);
        void print ();
        
    protected:
        vector <vector <T> > entries;
}

}
