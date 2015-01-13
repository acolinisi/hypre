/* Save a structured n x n mesh of square elements on the unit square into a
   GLVis mesh file with the given name. */
void GLVis_PrintGlobalSquareMesh(const char *meshfile, int n)
{
   FILE *file;

   int Dim = 2;
   int NumOfVertices = (n+1)*(n+1);
   int NumOfElements = n*n;

   int i, j;
   double x, y;
   double h = 1.0/n;

   if ((file = fopen(meshfile, "w")) == NULL)
   {
      printf("Error: can't open output file %s\n", meshfile);
      exit(1);
   }

   /* mesh header */
   fprintf(file, "MFEM mesh v1.0\n");
   fprintf(file, "\ndimension\n");
   fprintf(file, "%d\n", Dim);

   /* mesh elements */
   fprintf(file, "\nelements\n");
   fprintf(file, "%d\n", NumOfElements);
   for (j = 0; j < n; j++)
      for (i = 0; i < n; i++)
         fprintf(file, "1 3 %d %d %d %d\n", i + j*(n+1), i + 1 +j*(n+1),
                 i + 1 + (j+1)*(n+1), i + (j+1)*(n+1));

   /* boundary will be generated by GLVis */
   fprintf(file, "\nboundary\n");
   fprintf(file, "0\n");

   /* mesh vertices */
   fprintf(file, "\nvertices\n");
   fprintf(file, "%d\n", NumOfVertices);
   fprintf(file, "%d\n", Dim);
   for (j = 0; j < n+1; j++)
      for (i = 0; i < n+1; i++)
      {
         x = i*h;
         y = j*h;
         fprintf(file, "%.14e %.14e\n", x, y);
      }

   fflush(file);
   fclose(file);
}

/* Save a structured nx x ny mesh of square elements of size h, globally
   translated by (x0,y0), into a GLVis mesh file with the given prefix. */
void GLVis_PrintLocalSquareMesh(const char *meshfile_prefix, int nx, int ny,
                                double h, double x0, double y0, int myid)
{
   FILE *file;
   char meshfile[255];

   int Dim = 2;
   int NumOfVertices = (nx+1)*(ny+1);
   int NumOfElements = nx*ny;

   int i, j;
   double x, y;

   sprintf(meshfile, "%s.%06d", meshfile_prefix, myid);
   if ((file = fopen(meshfile, "w")) == NULL)
   {
      printf("Error: can't open output file %s\n", meshfile);
      exit(1);
   }

   /* mesh header */
   fprintf(file, "MFEM mesh v1.0\n");
   fprintf(file, "\ndimension\n");
   fprintf(file, "%d\n", Dim);

   /* mesh elements */
   fprintf(file, "\nelements\n");
   fprintf(file, "%d\n", NumOfElements);
   for (j = 0; j < ny; j++)
      for (i = 0; i < nx; i++)
         fprintf(file, "1 3 %d %d %d %d\n", i + j*(nx+1), i + 1 +j*(nx+1),
                 i + 1 + (j+1)*(nx+1), i + (j+1)*(nx+1));

   /* boundary will be generated by GLVis */
   fprintf(file, "\nboundary\n");
   fprintf(file, "0\n");

   /* mesh vertices */
   fprintf(file, "\nvertices\n");
   fprintf(file, "%d\n", NumOfVertices);
   fprintf(file, "%d\n", Dim);
   for (j = 0; j < ny+1; j++)
      for (i = 0; i < nx+1; i++)
      {
         x = x0+i*h;
         y = y0+j*h;
         fprintf(file, "%.14e %.14e\n", x, y);
      }

   fflush(file);
   fclose(file);
}

/* Save a structured n x n mesh of gamma-angled rhombuses, globally rotated by
   angle gamma*myid, into a GLVis mesh file with the given prefix. */
void GLVis_PrintLocalRhombusMesh(const char *meshfile_prefix,
                                 int n, int myid, double gamma)
{
   FILE *file;
   char meshfile[255];

   int Dim = 2;
   int NumOfVertices = (n+1)*(n+1);
   int NumOfElements = n*n;

   int i, j;
   double x, y;
   double h = 1.0/n;

   double rho = gamma*myid;
   double sg  = sin(gamma);
   double cg  = cos(gamma);
   double sr  = sin(rho);
   double cr  = cos(rho);

   sprintf(meshfile, "%s.%06d", meshfile_prefix, myid);
   if ((file = fopen(meshfile, "w")) == NULL)
   {
      printf("Error: can't open output file %s\n", meshfile);
      exit(1);
   }

   /* mesh header */
   fprintf(file, "MFEM mesh v1.0\n");
   fprintf(file, "\ndimension\n");
   fprintf(file, "%d\n", Dim);

   /* mesh elements */
   fprintf(file, "\nelements\n");
   fprintf(file, "%d\n", NumOfElements);
   for (j = 0; j < n; j++)
      for (i = 0; i < n; i++)
         fprintf(file, "1 3 %d %d %d %d\n", i + j*(n+1), i + 1 +j*(n+1),
                 i + 1 + (j+1)*(n+1), i + (j+1)*(n+1));

   /* boundary will be generated by GLVis */
   fprintf(file, "\nboundary\n");
   fprintf(file, "0\n");

   /* mesh vertices */
   fprintf(file, "\nvertices\n");
   fprintf(file, "%d\n", NumOfVertices);
   fprintf(file, "%d\n", Dim);
   for (j = 0; j < n+1; j++)
      for (i = 0; i < n+1; i++)
      {
         x = i*h + cg*j*h;
         y = sg*j*h;
         fprintf(file, "%.14e %.14e\n", cr*x - sr*y, sr*x + cr*y);
      }

   fflush(file);
   fclose(file);
}

/* Save a structured nx x ny x nz mesh of cubic elements of size h, globally
   translated by (x0,y0,z0), into a GLVis mesh file with the given prefix. */
void GLVis_PrintLocalCubicMesh(const char *meshfile_prefix,
                               int nx, int ny, int nz, double h,
                               double x0, double y0, double z0, int myid)
{
   FILE *file;
   char meshfile[255];

   int Dim = 3;
   int NumOfVertices = (nx+1)*(ny+1)*(nz+1);
   int NumOfElements = nx*ny*nz;

   int i, j, k;
   double x, y, z;

   sprintf(meshfile, "%s.%06d", meshfile_prefix, myid);
   if ((file = fopen(meshfile, "w")) == NULL)
   {
      printf("Error: can't open output file %s\n", meshfile);
      exit(1);
   }

   /* mesh header */
   fprintf(file, "MFEM mesh v1.0\n");
   fprintf(file, "\ndimension\n");
   fprintf(file, "%d\n", Dim);

   /* mesh elements */
   fprintf(file, "\nelements\n");
   fprintf(file, "%d\n", NumOfElements);
   for (k = 0; k < nz; k++)
      for (j = 0; j < ny; j++)
         for (i = 0; i < nx; i++)
            fprintf(file, "1 5 %d %d %d %d %d %d %d %d\n",
                    i + j*(nx+1) + k*(nx+1)*(ny+1),
                    i + 1 +j*(nx+1) + k*(nx+1)*(ny+1),
                    i + 1 + (j+1)*(nx+1) + k*(nx+1)*(ny+1),
                    i + (j+1)*(nx+1) + k*(nx+1)*(ny+1),
                    i + j*(nx+1) + (k+1)*(nx+1)*(ny+1),
                    i + 1 +j*(nx+1) + (k+1)*(nx+1)*(ny+1),
                    i + 1 + (j+1)*(nx+1) + (k+1)*(nx+1)*(ny+1),
                    i + (j+1)*(nx+1) + (k+1)*(nx+1)*(ny+1));

   /* boundary will be generated by GLVis */
   fprintf(file, "\nboundary\n");
   fprintf(file, "0\n");

   /* mesh vertices */
   fprintf(file, "\nvertices\n");
   fprintf(file, "%d\n", NumOfVertices);
   fprintf(file, "%d\n", Dim);
   for (k = 0; k < nz+1; k++)
      for (j = 0; j < ny+1; j++)
         for (i = 0; i < nx+1; i++)
         {
            x = x0+i*h;
            y = y0+j*h;
            z = z0+k*h;
            fprintf(file, "%.14e %.14e %.14e\n", x, y, z);
         }

   fflush(file);
   fclose(file);
}

#include "HYPRE_sstruct_mv.h"
#include "_hypre_sstruct_mv.h"

/* Save a GLVis mesh file with the given prefix corresponding to the input
   SStruct grid assuming that the cells in each part are the same. The optional
   trans and origin parameters specify the coordinate transformation for each
   part, relative to a square Cartesian grid. */
void GLVis_PrintSStructGrid(HYPRE_SStructGrid grid,
                            const char *meshfile_prefix, int myid,
                            double *trans, double *origin)
{
   FILE *file;
   char meshfile[255];

   int dim = ((hypre_SStructGrid *)grid)->ndim;
   int cellNV = (dim == 2) ? 4 : 8;
   int elemid = 2*dim-1;
   int nvert, nelem;

   hypre_StructGrid *part;
   int p, nparts = ((hypre_SStructGrid *)grid)->nparts;
   int given_trans = (trans != NULL && origin != NULL);
   double *T = trans, *O = origin;

   hypre_BoxArray *boxes;
   hypre_Box *box;
   int b, ncells;

   nvert = nelem = 0;
   for (p = 0; p < nparts; p++)
   {
      part = ((hypre_SStructGrid *)grid)->pgrids[p]->sgrids[0];
      boxes = hypre_StructGridBoxes(part);
      for (b = 0; b < hypre_BoxArraySize(boxes); b++)
      {
         box = hypre_BoxArrayBox(boxes, b);
         ncells = hypre_BoxVolume(box);
         nvert += ncells*cellNV;
         nelem += ncells;
      }
   }

   {
      int i, j, k, v, vert;
      double x0, y0, z0, h;

      sprintf(meshfile, "%s.%06d", meshfile_prefix, myid);
      if ((file = fopen(meshfile, "w")) == NULL)
      {
         printf("Error: can't open output file %s\n", meshfile);
         exit(1);
      }

      /* mesh header */
      fprintf(file, "MFEM mesh v1.0\n");
      fprintf(file, "\ndimension\n");
      fprintf(file, "%d\n", dim);

      /* mesh elements */
      fprintf(file, "\nelements\n");
      fprintf(file, "%d\n", nelem);

      vert = 0;
      for (p = 0; p < nparts; p++)
      {
         part = ((hypre_SStructGrid *)grid)->pgrids[p]->sgrids[0];
         boxes = hypre_StructGridBoxes(part);
         for (b = 0; b < hypre_BoxArraySize(boxes); b++)
         {
            box = hypre_BoxArrayBox(boxes, b);
            for (k = hypre_BoxIMinD(box,2); k <= hypre_BoxIMaxD(box,2); k++)
               for (j = hypre_BoxIMinD(box,1); j <= hypre_BoxIMaxD(box,1); j++)
                  for (i = hypre_BoxIMinD(box,0); i <= hypre_BoxIMaxD(box,0); i++)
                  {
                     fprintf(file, "1 %d ", elemid);
                     for (v = 0; v < cellNV; v++, vert++)
                        fprintf(file, "%d ", vert);
                     fprintf(file, "\n");
                  }
         }
      }

      /* boundary will be generated by GLVis */
      fprintf(file, "\nboundary\n");
      fprintf(file, "0\n");

      /* mesh vertices */
      fprintf(file, "\nvertices\n");
      fprintf(file, "%d\n", nvert);
      fprintf(file, "%d\n", dim);

      for (p = 0; p < nparts; p++)
      {
         part = ((hypre_SStructGrid *)grid)->pgrids[p]->sgrids[0];
         x0 = y0 = z0 = 0;
         h = 1.0;
         boxes = hypre_StructGridBoxes(part);
         for (b = 0; b < hypre_BoxArraySize(boxes); b++)
         {
            box = hypre_BoxArrayBox(boxes, b);
            for (k = hypre_BoxIMinD(box,2); k <= hypre_BoxIMaxD(box,2); k++)
               for (j = hypre_BoxIMinD(box,1); j <= hypre_BoxIMaxD(box,1); j++)
                  for (i = hypre_BoxIMinD(box,0); i <= hypre_BoxIMaxD(box,0); i++)
                     if (dim == 2)
                     {
                        if (!given_trans)
                        {
                           fprintf(file, "%.14e %.14e \n", x0+i*h, y0+j*h);
                           fprintf(file, "%.14e %.14e \n", x0+(i+1)*h, y0+j*h);
                           fprintf(file, "%.14e %.14e \n", x0+(i+1)*h, y0+(j+1)*h);
                           fprintf(file, "%.14e %.14e \n", x0+i*h, y0+(j+1)*h);
                        }
                        else
                        {
                           fprintf(file, "%.14e %.14e \n",
                                   T[0]*i+T[1]*j+O[0],
                                   T[2]*i+T[3]*j+O[1]);
                           fprintf(file, "%.14e %.14e \n",
                                   T[0]*(i+1)+T[1]*j+O[0],
                                   T[2]*(i+1)+T[3]*j+O[1]);
                           fprintf(file, "%.14e %.14e \n",
                                   T[0]*(i+1)+T[1]*(j+1)+O[0],
                                   T[2]*(i+1)+T[3]*(j+1)+O[1]);
                           fprintf(file, "%.14e %.14e \n",
                                   T[0]*i+T[1]*(j+1)+O[0],
                                   T[2]*i+T[3]*(j+1)+O[1]);
                        }
                     }
                     else
                     {
                        if (!given_trans)
                        {
                           fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+j*h, z0+k*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+j*h, z0+k*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+(j+1)*h, z0+k*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+(j+1)*h, z0+k*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+j*h, z0+(k+1)*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+j*h, z0+(k+1)*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+(j+1)*h, z0+(k+1)*h);
                           fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+(j+1)*h, z0+(k+1)*h);
                        }
                        else
                        {
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*i+T[1]*j+T[2]*k+O[0],
                                   T[3]*i+T[4]*j+T[5]*k+O[1],
                                   T[6]*i+T[7]*j+T[8]*k+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*(i+1)+T[1]*j+T[2]*k+O[0],
                                   T[3]*(i+1)+T[4]*j+T[5]*k+O[1],
                                   T[6]*(i+1)+T[7]*j+T[8]*k+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*(i+1)+T[1]*(j+1)+T[2]*k+O[0],
                                   T[3]*(i+1)+T[4]*(j+1)+T[5]*k+O[1],
                                   T[6]*(i+1)+T[7]*(j+1)+T[8]*k+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*i+T[1]*(j+1)+T[2]*k+O[0],
                                   T[3]*i+T[4]*(j+1)+T[5]*k+O[1],
                                   T[6]*i+T[7]*(j+1)+T[8]*k+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*i+T[1]*j+T[2]*(k+1)+O[0],
                                   T[3]*i+T[4]*j+T[5]*(k+1)+O[1],
                                   T[6]*i+T[7]*j+T[8]*(k+1)+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*(i+1)+T[1]*j+T[2]*(k+1)+O[0],
                                   T[3]*(i+1)+T[4]*j+T[5]*(k+1)+O[1],
                                   T[6]*(i+1)+T[7]*j+T[8]*(k+1)+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*(i+1)+T[1]*(j+1)+T[2]*(k+1)+O[0],
                                   T[3]*(i+1)+T[4]*(j+1)+T[5]*(k+1)+O[1],
                                   T[6]*(i+1)+T[7]*(j+1)+T[8]*(k+1)+O[2]);
                           fprintf(file, "%.14e %.14e %.14e \n",
                                   T[0]*i+T[1]*(j+1)+T[2]*(k+1)+O[0],
                                   T[3]*i+T[4]*(j+1)+T[5]*(k+1)+O[1],
                                   T[6]*i+T[7]*(j+1)+T[8]*(k+1)+O[2]);
                        }
                     }
         }

         if (given_trans)
         {
            T += dim*dim;
            O += dim;
         }
      }

      fflush(file);
      fclose(file);
   }
}

/* Save a GLVis grid function (in a file with the given prefix) corresponding to
   the values of the input SStruct vector restricted to the specified SStruct
   variable. Currently only CELL and NODE variable types are supported. */
void GLVis_PrintSStructVector(HYPRE_SStructVector sol,
                              int var,
                              const char *solfile_prefix,
                              int myid)
{
   FILE *file;
   char solfile[255];

   hypre_SStructGrid *grid = ((hypre_SStructVector*)sol)->grid;
   int dim = grid->ndim;

   hypre_StructGrid *part;
   int p, nparts = grid->nparts;
   hypre_BoxArray *boxes;
   hypre_Box *box;
   int b;

   int i, j, k, ni, nj, nk;
   double *values;
   int ilower[3], iupper[3];

   HYPRE_SStructVariable vartype = grid->pgrids[0]->vartypes[var];

   char fe_coll[100];
   int var_off;

   sprintf(solfile, "%s.%06d", solfile_prefix, myid);
   if ((file = fopen(solfile, "w")) == NULL)
   {
      printf("Error: can't open output file %s\n", solfile);
      exit(1);
   }

   /* set the finite element collection based on variable type */
   switch (vartype)
   {
      case HYPRE_SSTRUCT_VARIABLE_CELL:
         sprintf(fe_coll, "%s", "Local_L2_2D_P0");
         var_off = 0;
         break;
      case HYPRE_SSTRUCT_VARIABLE_NODE:
         sprintf(fe_coll, "%s", "Local_H1_2D_P1");
         var_off = 1;
         break;
      default:
         printf("Error: unsuported variable type\n");
         exit(1);
   }

   /* grid function header */
   fprintf(file, "FiniteElementSpace\n");
   fprintf(file, "FiniteElementCollection: %s\n", fe_coll);
   fprintf(file, "VDim: 1\n");
   fprintf(file, "Ordering: 0\n\n");

   /* extract and save the vector values on each cell */
   for (p = 0; p < nparts; p++)
   {
      part = grid->pgrids[p]->sgrids[0];
      boxes = hypre_StructGridBoxes(part);
      for (b = 0; b < hypre_BoxArraySize(boxes); b++)
      {
         box = hypre_BoxArrayBox(boxes, b);
         ni = hypre_BoxSizeD(box,0);
         nj = hypre_BoxSizeD(box,1);
         nk = hypre_BoxSizeD(box,2);

         ilower[0] = hypre_BoxIMinD(box,0) - var_off;
         ilower[1] = hypre_BoxIMinD(box,1) - var_off;
         iupper[0] = hypre_BoxIMaxD(box,0);
         iupper[1] = hypre_BoxIMaxD(box,1);

         if (dim == 2)
            values = (double*) malloc((ni+var_off)*(nj+var_off)*sizeof(double));
         else
         {
            values = (double*) malloc((ni+var_off)*(nj+var_off)*(nk+var_off)*sizeof(double));
            ilower[2] = hypre_BoxIMinD(box,2) - var_off;
            iupper[2] = hypre_BoxIMaxD(box,2);
         }

         HYPRE_SStructVectorGetBoxValues(sol, p, ilower, iupper, var, values);

         if (vartype == HYPRE_SSTRUCT_VARIABLE_CELL)
         {
            for (k = 0; k < nk; k++)
               for (j = 0; j < nj; j++)
                  for (i = 0; i < ni; i++)
                     fprintf(file, "%.14e\n", values[i + j*ni]);
         }
         else if (vartype == HYPRE_SSTRUCT_VARIABLE_NODE)
         {
            if (dim == 2)
            {
               for (j = 0; j < nj; j++)
                  for (i = 0; i < ni; i++)
                  {
                     fprintf(file, "%.14e\n", values[i + j*(ni+1)]);
                     fprintf(file, "%.14e\n", values[i+1 + j*(ni+1)]);
                     fprintf(file, "%.14e\n", values[i+1 + (j+1)*(ni+1)]);
                     fprintf(file, "%.14e\n", values[i + (j+1)*(ni+1)]);
                  }
            }
            else
            {
               for (k = 0; k < nk; k++)
                  for (j = 0; j < nj; j++)
                     for (i = 0; i < ni; i++)
                     {
                        fprintf(file, "%.14e\n", values[i + j*(ni+1) + k*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i+1 + j*(ni+1) + k*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i+1 + (j+1)*(ni+1) + k*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i + (j+1)*(ni+1) + k*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i + j*(ni+1) + (k+1)*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i+1 + j*(ni+1) + (k+1)*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i+1 + (j+1)*(ni+1) + (k+1)*(ni+1)*(nj+1)]);
                        fprintf(file, "%.14e\n", values[i + (j+1)*(ni+1) + (k+1)*(ni+1)*(nj+1)]);
                     }
            }
         }

         free(values);
      }
   }

   fflush(file);
   fclose(file);
}

/* Save a GLVis mesh file with the given prefix corresponding to the input
   Struct grid assuming that the cells are the same. The optional trans and
   origin parameters specify a coordinate transformation, relative to a square
   Cartesian grid. */
void GLVis_PrintStructGrid(HYPRE_StructGrid Grid,
                           const char *meshfile_prefix, int myid,
                           double *trans, double *origin)
{
   FILE *file;
   char meshfile[255];

   hypre_StructGrid *grid = (hypre_StructGrid *)Grid;
   int dim = grid->ndim;
   int cellNV = (dim == 2) ? 4 : 8;
   int elemid = 2*dim-1;
   int nvert, nelem;

   int given_trans = (trans != NULL && origin != NULL);
   double *T = trans, *O = origin;

   hypre_BoxArray *boxes;
   hypre_Box *box;
   int b, ncells;

   nvert = nelem = 0;
   boxes = hypre_StructGridBoxes(grid);
   for (b = 0; b < hypre_BoxArraySize(boxes); b++)
   {
      box = hypre_BoxArrayBox(boxes, b);
      ncells = hypre_BoxVolume(box);
      nvert += ncells*cellNV;
      nelem += ncells;
   }

   {
      int i, j, k, v, vert;
      double x0, y0, z0, h;

      sprintf(meshfile, "%s.%06d", meshfile_prefix, myid);
      if ((file = fopen(meshfile, "w")) == NULL)
      {
         printf("Error: can't open output file %s\n", meshfile);
         exit(1);
      }

      /* mesh header */
      fprintf(file, "MFEM mesh v1.0\n");
      fprintf(file, "\ndimension\n");
      fprintf(file, "%d\n", dim);

      /* mesh elements */
      fprintf(file, "\nelements\n");
      fprintf(file, "%d\n", nelem);

      vert = 0;

      boxes = hypre_StructGridBoxes(grid);
      for (b = 0; b < hypre_BoxArraySize(boxes); b++)
      {
         box = hypre_BoxArrayBox(boxes, b);
         for (k = hypre_BoxIMinD(box,2); k <= hypre_BoxIMaxD(box,2); k++)
            for (j = hypre_BoxIMinD(box,1); j <= hypre_BoxIMaxD(box,1); j++)
               for (i = hypre_BoxIMinD(box,0); i <= hypre_BoxIMaxD(box,0); i++)
               {
                  fprintf(file, "1 %d ", elemid);
                  for (v = 0; v < cellNV; v++, vert++)
                     fprintf(file, "%d ", vert);
                  fprintf(file, "\n");
               }
      }

      /* boundary will be generated by GLVis */
      fprintf(file, "\nboundary\n");
      fprintf(file, "0\n");

      /* mesh vertices */
      fprintf(file, "\nvertices\n");
      fprintf(file, "%d\n", nvert);
      fprintf(file, "%d\n", dim);

      x0 = y0 = z0 = 0;
      h = 1.0;
      boxes = hypre_StructGridBoxes(grid);
      for (b = 0; b < hypre_BoxArraySize(boxes); b++)
      {
         box = hypre_BoxArrayBox(boxes, b);
         for (k = hypre_BoxIMinD(box,2); k <= hypre_BoxIMaxD(box,2); k++)
            for (j = hypre_BoxIMinD(box,1); j <= hypre_BoxIMaxD(box,1); j++)
               for (i = hypre_BoxIMinD(box,0); i <= hypre_BoxIMaxD(box,0); i++)
                  if (dim == 2)
                  {
                     if (!given_trans)
                     {
                        fprintf(file, "%.14e %.14e \n", x0+i*h, y0+j*h);
                        fprintf(file, "%.14e %.14e \n", x0+(i+1)*h, y0+j*h);
                        fprintf(file, "%.14e %.14e \n", x0+(i+1)*h, y0+(j+1)*h);
                        fprintf(file, "%.14e %.14e \n", x0+i*h, y0+(j+1)*h);
                     }
                     else
                     {
                        fprintf(file, "%.14e %.14e \n",
                                T[0]*i+T[1]*j+O[0],
                                T[2]*i+T[3]*j+O[1]);
                        fprintf(file, "%.14e %.14e \n",
                                T[0]*(i+1)+T[1]*j+O[0],
                                T[2]*(i+1)+T[3]*j+O[1]);
                        fprintf(file, "%.14e %.14e \n",
                                T[0]*(i+1)+T[1]*(j+1)+O[0],
                                T[2]*(i+1)+T[3]*(j+1)+O[1]);
                        fprintf(file, "%.14e %.14e \n",
                                T[0]*i+T[1]*(j+1)+O[0],
                                T[2]*i+T[3]*(j+1)+O[1]);
                     }
                  }
                  else
                  {
                     if (!given_trans)
                     {
                        fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+j*h, z0+k*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+j*h, z0+k*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+(j+1)*h, z0+k*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+(j+1)*h, z0+k*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+j*h, z0+(k+1)*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+j*h, z0+(k+1)*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+(i+1)*h, y0+(j+1)*h, z0+(k+1)*h);
                        fprintf(file, "%.14e %.14e %.14e \n", x0+i*h, y0+(j+1)*h, z0+(k+1)*h);
                     }
                     else
                     {
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*i+T[1]*j+T[2]*k+O[0],
                                T[3]*i+T[4]*j+T[5]*k+O[1],
                                T[6]*i+T[7]*j+T[8]*k+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*(i+1)+T[1]*j+T[2]*k+O[0],
                                T[3]*(i+1)+T[4]*j+T[5]*k+O[1],
                                T[6]*(i+1)+T[7]*j+T[8]*k+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*(i+1)+T[1]*(j+1)+T[2]*k+O[0],
                                T[3]*(i+1)+T[4]*(j+1)+T[5]*k+O[1],
                                T[6]*(i+1)+T[7]*(j+1)+T[8]*k+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*i+T[1]*(j+1)+T[2]*k+O[0],
                                T[3]*i+T[4]*(j+1)+T[5]*k+O[1],
                                T[6]*i+T[7]*(j+1)+T[8]*k+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*i+T[1]*j+T[2]*(k+1)+O[0],
                                T[3]*i+T[4]*j+T[5]*(k+1)+O[1],
                                T[6]*i+T[7]*j+T[8]*(k+1)+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*(i+1)+T[1]*j+T[2]*(k+1)+O[0],
                                T[3]*(i+1)+T[4]*j+T[5]*(k+1)+O[1],
                                T[6]*(i+1)+T[7]*j+T[8]*(k+1)+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*(i+1)+T[1]*(j+1)+T[2]*(k+1)+O[0],
                                T[3]*(i+1)+T[4]*(j+1)+T[5]*(k+1)+O[1],
                                T[6]*(i+1)+T[7]*(j+1)+T[8]*(k+1)+O[2]);
                        fprintf(file, "%.14e %.14e %.14e \n",
                                T[0]*i+T[1]*(j+1)+T[2]*(k+1)+O[0],
                                T[3]*i+T[4]*(j+1)+T[5]*(k+1)+O[1],
                                T[6]*i+T[7]*(j+1)+T[8]*(k+1)+O[2]);
                     }
                  }

         if (given_trans)
         {
            T += dim*dim;
            O += dim;
         }
      }

      fflush(file);
      fclose(file);
   }
}

/* Save a Q0 GLVis grid function (in a file with the given prefix) corresponding
   to the values of the input Struct vector. */
void GLVis_PrintStructVector(HYPRE_StructVector sol,
                             const char *solfile_prefix,
                             int myid)
{
   FILE *file;
   char solfile[255];

   hypre_StructGrid *grid = ((hypre_StructVector*)sol)->grid;
   int dim = grid->ndim;

   hypre_BoxArray *boxes;
   hypre_Box *box;
   int b;

   int i, j, k, ni, nj, nk;
   double *values;
   int ilower[3], iupper[3];

   sprintf(solfile, "%s.%06d", solfile_prefix, myid);
   if ((file = fopen(solfile, "w")) == NULL)
   {
      printf("Error: can't open output file %s\n", solfile);
      exit(1);
   }

   /* grid function header */
   fprintf(file, "FiniteElementSpace\n");
   fprintf(file, "FiniteElementCollection: Local_L2_2D_P0\n");
   fprintf(file, "VDim: 1\n");
   fprintf(file, "Ordering: 0\n\n");

   /* extract and save the vector values on each cell */
   boxes = hypre_StructGridBoxes(grid);
   for (b = 0; b < hypre_BoxArraySize(boxes); b++)
   {
      box = hypre_BoxArrayBox(boxes, b);
      ni = hypre_BoxSizeD(box,0);
      nj = hypre_BoxSizeD(box,1);
      nk = hypre_BoxSizeD(box,2);

      ilower[0] = hypre_BoxIMinD(box,0);
      ilower[1] = hypre_BoxIMinD(box,1);
      iupper[0] = hypre_BoxIMaxD(box,0);
      iupper[1] = hypre_BoxIMaxD(box,1);

      if (dim == 2)
         values = (double*) malloc(ni*nj*sizeof(double));
      else
      {
         values = (double*) malloc(ni*nj*nk*sizeof(double));
         ilower[2] = hypre_BoxIMinD(box,2);
         iupper[2] = hypre_BoxIMaxD(box,2);
      }

      HYPRE_StructVectorGetBoxValues(sol, ilower, iupper, values);

      for (k = 0; k < nk; k++)
         for (j = 0; j < nj; j++)
            for (i = 0; i < ni; i++)
               fprintf(file, "%.14e\n", values[i + j*ni]);

      free(values);
   }

   fflush(file);
   fclose(file);
}

/* Save additional data needed for GLVis visualization (e.g. the number of
   processors in the run). */
void GLVis_PrintData(const char *datafile, int myid, int num_procs)
{
   FILE *file;

   if (myid == 0)
   {
      file = fopen(datafile, "w");
      fprintf(file, "np %d\n", num_procs);
      fflush(file);
      fclose(file);
   }
}
