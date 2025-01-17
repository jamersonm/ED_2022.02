#include <stdlib.h>

#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix2D
{
    protected:
        T** ptrMatrixElementos;
        unsigned int nLin, nCol;

    private:
        void init(unsigned nLin=1, unsigned nCol=1, T defaultValue = NULL)
        {
            unsigned int idxLin, idxCol;

            this->nLin = nLin;
            this->nCol = nCol;

            // aloca referencias para as linhas
            this->ptrMatrixElementos = new T*[this->nLin];

            // aloca referencias para os elementos
            for(idxLin=0; idxLin<this->nLin; idxLin++)
                this->ptrMatrixElementos[idxLin] = new T[this->nCol];

            // seta NULL para as referencias para os elementos
            for(idxLin=0; idxLin<this->nLin; idxLin++)
                for(idxCol=0; idxCol<this->nCol; idxCol++)
                    this->ptrMatrixElementos[idxLin][idxCol] = NULL;
        }
    public:
        //-----------------------------------------------------------------
        Matrix2D()
        {
            init(5, 5);
        }
        //-----------------------------------------------------------------
        Matrix2D(unsigned int _nLin, unsigned int _nCol)
        {
            this->init(_nLin, _nCol);
        }
        //-----------------------------------------------------------------
        ~Matrix2D()
        {
            unsigned int idxLin, idxCol;

            // libera as linhas
            for(idxLin=0; idxLin<this->nLin; idxLin++)
                delete []this->ptrMatrixElementos[idxLin];

            // libera o array de linhas
            delete []this->ptrMatrixElementos;

            this->nLin = 0;
            this->nCol = 0;

            this->ptrMatrixElementos = NULL;
        }

        //-----------------------------------------------------------------
        T getElemento(unsigned int idxLin, unsigned int idxCol)
        {
            if (idxLin >= this->nLin || idxCol >= this->nCol)
                return NULL;

            return this->ptrMatrixElementos[idxLin][idxCol];
        }

        //-----------------------------------------------------------------
        unsigned int setElemento(unsigned int idxLin, unsigned int idxCol, T ptrElemento)
        {
            if (idxLin >= this->nLin || idxCol >= this->nCol)
                return 0;

            this->ptrMatrixElementos[idxLin][idxCol] = ptrElemento;

            return +1;
        }

        //-----------------------------------------------------------------
        unsigned int getNLin()
        {
            return this->nLin;
        }

        //-----------------------------------------------------------------
        unsigned int getNCol()
        {
            return this->nCol;
        }

        //-----------------------------------------------------------------
        T getSoma()
        {
            T soma = 0;
            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    soma += getElemento(i, j);
            return soma;
        }

        //-----------------------------------------------------------------
        T getProduto()
        {
            T produto = 1;
            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    produto *= getElemento(i, j);
            return produto;
        }

        //-----------------------------------------------------------------
        void multiplicaK()
        {
            T K;
            std::cout << "Informe o valor de K: ";
            std::cin >> K;
            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    setElemento(i, j, (getElemento(i, j) * K));
        }

        //-----------------------------------------------------------------
        int verificaNula()
        {
            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    if(getElemento(i, j) != 0)
                        return 0;
            return 1;
        }

        //-----------------------------------------------------------------
        int verificaDiagonal()
        {
            if(verificaNula() == 1)
                return 0;

            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    if(i != j && getElemento(i,j) != 0)
                        return 0;
            return 1;
        }

        //-----------------------------------------------------------------
        int verificaIdentidade()
        {
            if(verificaNula() == 1)
                return 0;

            if(verificaDiagonal() == 1)
                for(int i = 0; i < getNLin(); i++)
                    for(int j = 0; j < getNCol(); j++)
                        if(i == j && getElemento(i,j) != 1)
                            return 0;
                        else
                            return 1;
            return 0;
        }

        //-----------------------------------------------------------------
        int verificaEscalar()
        {
            if(verificaNula() == 1)
                return 0;

            T escalar;
            if(verificaDiagonal() == 1)
            {
                for(int i = 0; i < getNLin(); i++)
                    for(int j = 0; j < getNCol(); j++)
                        if(i == j)
                            escalar = getElemento(i, j);

                for(int i = 0; i < getNLin(); i++)
                    for(int j = 0; j < getNCol(); j++)
                        if(i == j && escalar != getElemento(i, j))
                            return 0;
                        else
                            return 1;
            }
            return 0;
        }

        //-----------------------------------------------------------------
        int verificaSimetrica()
        {
            if(verificaNula() == 1)
                return 0;

            if(getNLin() != getNCol())
                std::cout << "A matriz n�o � quadrada." << std::endl;
                return 0;

            T transposta[getNLin()][getNCol()];
            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    transposta[j][i] = getElemento(i, j);

            for(int i = 0; i < getNLin(); i++)
                for(int j = 0; j < getNCol(); j++)
                    if(transposta[i][j] != getElemento(i,j))
                        return 0;
            return 1;
        }

        //-----------------------------------------------------------------
        int verificaAntiSimetrica()
        {
            if(verificaSimetrica() == 0)
                return 0;

            for(int i = 0; i < getNLin(); i++)
                    for(int j = 0; j < getNCol(); j++)
                        if(i == j && getElemento(i,j) != 0)
                            return 0;
            return 1;
        }

};

#endif // MATRIX_H
