

#include <iostream>
#include <stdio.h>




struct V
{

	V()
	{
	p=NULL;
	l=NULL;
	m=NULL;
	r=NULL;
	}
V *p;
int field1;
int field2;

V  *l;
V  *m;
V  *r;
};

bool notlist (V*ver)
{
	bool n=true;
	if (((ver->l==NULL)&&(ver->m==NULL))&&(ver->r==NULL))
	{n=false;}
return n;
}


void upd_v(V*root)
{
	V *verhina=new V;
	if (root->m!=NULL)
	{
		verhina=root->m;

	while ((notlist(verhina)))
	{
		verhina=verhina->l;
	}

	root->field1=verhina->field1;
	}
	if (root->r!=NULL)
	{
		verhina=root->r;

		while ((notlist(verhina)))
			{
				verhina=verhina->l;
			}

			root->field2=verhina->field1;
	}
}






void addV(int number,V *root)
{
	V *verhina=new V;
	verhina=root;
int l=0; // 0-left 1-middle 2-right


	// if we have root only
	if ((!(notlist(verhina)))&(verhina->p==NULL))
	{
		verhina->l=new V;
		verhina->l->field1=number;
		verhina->l->p=verhina;
		return;
	}

	// if we have root and left son

	if (((verhina->p==NULL)&&(verhina->l!=NULL))&&(verhina->m==NULL))
	{
		if ((verhina->l->field1)<number)
		{
		verhina->m=new V;
		verhina->m->field1=number;
		verhina->m->p=verhina;
		verhina->field1=number;
		}
		else
		{
			verhina->m=new V;
			verhina->m->field1=verhina->l->field1;
			verhina->m->p=verhina;
			verhina->field1=verhina->l->field1;
			verhina->l->field1=number;
			}
		verhina->m->p=verhina;
		return ;
	}


	while (notlist(verhina)) //screach from root to insert list
	{
		if (verhina->r==NULL) // 1f_2v
		{
				if (number>=verhina->field1)
				{
					verhina=verhina->m;
					l=1;
				}
				else
				{
					verhina=verhina->l;
					l=0;
				}
		}
		else  //2f_3v
		{

			if (number>=verhina->field1)
			{
				if (number>=verhina->field2)
				{
				verhina=verhina->r;
				l=2;
				}
				else
				{
					verhina=verhina->m;
					l=1;
				}
			}
			else
			{
				verhina=verhina->l;
				l=0;
			}


		}


	}

	//verhina=verhina->p; // we need the parent not a list!

	//we have the list


//1 trivial way we have 1 empty son

if (verhina->p->r==NULL)
{
	verhina->p->r=new V;
	verhina->p->r->p=verhina->p;
if (number>verhina->p->m->field1)
{
	verhina->p->r->field1=number;
}
else
{
	if (number>verhina->p->l->field1)
	{
		verhina->p->r->field1=verhina->p->m->field1;
		verhina->p->m->field1=number;
	}
	else
	{
		verhina->p->r->field1=verhina->p->m->field1;
		verhina->p->m->field1=verhina->p->l->field1;
		verhina->p->l->field1=number;
	}
}

upd_v(verhina->p);
return ;
}



// 2 trivial way we NOT have 1 empty son

verhina=verhina->p->l;
if (verhina->p->r!=NULL)
{
	V *buf1,*buf2,*Gbuf;

	buf1=new V;
	buf2=new V;
	Gbuf=new V;

	buf1=verhina->p->r;
	verhina->p->r=NULL;


	if (l==0)
	{
		buf2->field1=verhina->p->m->field1;
		if (number>verhina->p->l->field1)
		{
			verhina->p->m->field1=number;
		}
		else
		{
			verhina->p->m->field1=verhina->p->l->field1;
			verhina->p->l->field1=number;
		}
	}
	else
	{
		buf2->field1=number;
	}


	if (buf1->field1>buf2->field1)
	{
		Gbuf->l=buf2;
		Gbuf->m=buf1;

		Gbuf->l->p=Gbuf;
		Gbuf->m->p=Gbuf;

		Gbuf->field1=Gbuf->m->field1;
	}
	else
	{
		Gbuf->l=buf1;
		Gbuf->m=buf2;

		Gbuf->l->p=Gbuf;
		Gbuf->m->p=Gbuf;

		Gbuf->field1=Gbuf->m->field1;

	}

	verhina->p->field1=verhina->p->m->field1;

// we split off verh
	verhina=verhina->p->l;

while (verhina->p!=NULL)
{	// cycle begin
verhina=verhina->p;

if (verhina->p!=NULL)
{

if (verhina->p->r==NULL)
{
	buf1=new V;
	buf2=new V;

	buf1=Gbuf;
	Gbuf=new V;

	if (buf1->field1>verhina->p->m->field1)
	{
		//Gbuf pravee middle verh
		verhina->p->r=new V;
		verhina->p->r=buf1;

	}
	else
	{
	//Gbuf levee middle verh and pravee left
		verhina->p->r=new V;
		verhina->p->r=verhina->p->m;

		verhina->p->m=new V;
		verhina->p->m=buf1;
		verhina->p->m->p=verhina->p;
	}

	verhina->p->r->p=verhina->p;
	upd_v(verhina->p);


	break;
}
else // cycle part
{

buf1=new V;
buf1=new V;
buf2=new V;

buf1=Gbuf;
Gbuf=new V;

verhina=verhina->p->l;

if (buf1->field1>verhina->p->m->field1)
{
//Gbuf pravee middle verh
	if (buf1->field1>verhina->p->r->field1)
	{
		//Gbuf pravee right verh
		buf2=verhina->p->r;
		verhina->p->r=NULL;
		Gbuf->l=buf2;
		Gbuf->m=buf1;


	}
	else
	{
		//Gbuf pravee middle verh and levee right

		buf2=verhina->p->r;
		verhina->p->r=NULL;
		Gbuf->l=buf1;
		Gbuf->m=buf2;

	}

}
else
{
//Gbuf levee middle verh and pravee left
	buf2=verhina->p->r;
	verhina->p->r=NULL;
	Gbuf->l=verhina->p->m;
	Gbuf->m=buf2;
	verhina->p->m=new V;
	verhina->p->m=buf1;
}

verhina->p->m->p=verhina->p;
Gbuf->l->p=Gbuf;
Gbuf->m->p=Gbuf;

upd_v(Gbuf);
upd_v(verhina->p);


}



} // verhina->p!=NULL
else // verhina->p==NULL
{


	// u nas tolko 2 verh;
	buf1=new V;
	buf2=new V;

	/*
if (verhina->field1>Gbuf->field1)
{
	buf1=Gbuf;
	buf2=verhina;
}
else
{
	buf2=Gbuf;
	buf1=verhina;
}
*/

	//
	buf1=verhina;
	buf2=Gbuf;
	//
	// gemor with root!!!!
	Gbuf=new V;
	Gbuf->l=buf1->l;
	Gbuf->m=buf1->m;
	Gbuf->l->p=Gbuf;
	Gbuf->m->p=Gbuf;
upd_v(Gbuf);
	buf1=Gbuf;

	//gemor end


root->l=buf1;
root->m=buf2;

root->l->p=root;
root->m->p=root;

upd_v(root);


break;

}// verhina->p=NULL
} // cycle over
} //over 2way



//over addV
}






bool allson(V*root)
{
bool k=false;
if (((root->l!=NULL)&&(root->m!=NULL))&&(root->r!=NULL))
{
	k=true;
}
return k;
}








void delV(int number,V *root)
{
	V *verhina=new V;
	verhina=root;
int l=0; // 0-left 1-middle 2-right



	while (notlist(verhina)) //screach from root to insert list
	{
		if (verhina->r==NULL) // 1f_2v
		{
				if (number>=verhina->field1)
				{
					verhina=verhina->m;
					l=1;
				}
				else
				{
					verhina=verhina->l;
					l=0;
				}
		}
		else  //2f_3v
		{

			if (number>=verhina->field1)
			{
				if (number>=verhina->field2)
				{
				verhina=verhina->r;
				l=2;
				}
				else
				{
					verhina=verhina->m;
					l=1;
				}
			}
			else
			{
				verhina=verhina->l;
				l=0;
			}


		}


	}

if (number!=verhina->field1)
{
	printf("this tree not have this number \n");
	return;
}

// 1 way have 3 lista in verh
if (allson(verhina->p))
{
	switch(l)
	{
	case 0:
		verhina->p->l=verhina->p->m;
		verhina->p->m=new V;
		verhina->p->m=verhina->p->r;
		verhina->p->r=NULL;
		break;
	case 1:
		verhina->p->m=verhina->p->r;
		verhina->p->r=NULL;
		break;
	case 2:
		verhina->p->r=NULL;
		break;
	}
	upd_v(verhina->p);
}
else               // 2 way we have 2 lista in verh
{

	if (verhina->p->p==NULL) // we are in root!
	{
		switch(l)
		{
		case 0:
			if (verhina->p->m!=NULL)
			{
			verhina->p->l=verhina->p->m;
			verhina->p->m=NULL;
			}
			else
			{
				verhina->p->l=NULL;
			}
			break;
		case 1:
			verhina->p->m=NULL;
			break;
		}
		if(verhina->p->l!=NULL)
		{
		verhina->p->field1=verhina->p->l->field1+1;
		}

	}
	else // we are not in root!
	{
		if (verhina->p->p->r==NULL)
		{
			// grandfather have only 2 father
			if(verhina->p->field1<verhina->p->p->field1)
			{
				// we are in left father
				if (allson(verhina->p->p->m))
				{// middle father have 3 son, we can give one!
					switch(l)
					{
					case 0:
						verhina->p->l=verhina->p->m;
						verhina->p->m=new V;
						verhina->p->m=verhina->p->p->m->l;
						verhina->p->m->p=verhina->p;
						break;
					case 1:
						verhina->p->m=verhina->p->p->m->l;
						break;
					}
						verhina->p->p->m->l=new V;
						verhina->p->p->m->l=verhina->p->p->m->m;
						verhina->p->p->m->m=new V;
						verhina->p->p->m->m=verhina->p->p->m->r;
						verhina->p->p->m->r=NULL;

					upd_v(verhina->p);
					upd_v(verhina->p->p);
					upd_v(verhina->p->p->m);
					return;
				} // if (allson(verhina->p->p->m))
			} // we are in left father
			else
			{
					// we are in middle father
		if (allson(verhina->p->p->l))
			{// left father have 3 son, we can give one!
					switch(l)
					{
						case 0:
						verhina->p->l=verhina->p->p->l->r;
						verhina->p->l->p=verhina->p;
							break;
						case 1:
						verhina->p->m=verhina->p->l;
						verhina->p->l=new V;
						verhina->p->l=verhina->p->p->l->r;
						verhina->p->l->p=verhina->p;
							break;
					}

				verhina->p->p->l->r=NULL;

			upd_v(verhina->p);
			upd_v(verhina->p->p);
			upd_v(verhina->p->p->l);
			return;
			}

			} // we are in middle father

			////////////////////the worst situation! we need delete not only 1 verh


			if(verhina->p->field1<verhina->p->p->field1)
			{
			// we are in left father
				verhina->p->p->m->r=new V;
				verhina->p->p->m->r=verhina->p->p->m->m;
				verhina->p->p->m->m=new V;
				verhina->p->p->m->m=verhina->p->p->m->l;
				verhina->p->p->m->l=new V;
				switch(l)
				{
					case 0:
						verhina->p->p->m->l=verhina->p->m;
						verhina->p->p->m->l->p=verhina->p->p->m;
						break;
					case 1:
						verhina->p->p->m->l=verhina->p->l;
						verhina->p->p->m->l->p=verhina->p->p->m;
						break;
				}

				upd_v(verhina->p->p);
				upd_v(verhina->p->p->m);
				verhina->p->p->l=verhina->p->p->m;
				verhina->p->p->field1=verhina->p->p->l->m->field1;
				verhina=verhina->p->p->l->l;
				verhina->p->p->m=NULL;
			}
			else
			{
				// we are in middle father

				verhina->p->p->l->r=new V;
				switch(l)
								{
									case 0:
										verhina->p->p->l->r=verhina->p->p->m->m;
										verhina->p->p->l->r->p=verhina->p->p->l;
										break;
									case 1:
										verhina->p->p->l->r=verhina->p->p->m->l;
										verhina->p->p->l->r->p=verhina->p->p->l;
										break;
								}
				upd_v(verhina->p->p);
				upd_v(verhina->p->p->l);
				verhina->p->p->field1=verhina->p->p->l->m->field1;
				verhina->p->p->m=NULL;
			}

			verhina=verhina->p->p;




	// cycle begin
	while (verhina->p!=NULL)
	{// cycle end
		if (verhina->p->r!=NULL)
		{
			if (verhina->field1>verhina->p->field1)
			{
				if (verhina->field1>verhina->p->field2)
					{// in right son
						if (allson(verhina->p->m))
							{
									verhina->m=new V;
									verhina->m=verhina->l;
									verhina->l=new V;
									verhina->l=verhina->p->m->r;
									verhina->l->p=verhina;

									verhina->p->m->r=NULL;

									upd_v(verhina);
									upd_v(verhina->p);
									return;
							}
						if (allson(verhina->p->l))
							{
							verhina->m=new V;
							verhina->m=verhina->l;
							verhina->l=new V;
							verhina->l=verhina->p->m->m;
							verhina->l->p=verhina;
							verhina->p->m->m=new V;
							verhina->p->m->m=verhina->p->m->l;
							verhina->p->m->l=new V;
							verhina->p->m->l=verhina->p->l->r;
							verhina->p->m->l->p=verhina->p->m;

							verhina->p->l->r=NULL;

							upd_v(verhina);
							upd_v(verhina->p);
							upd_v(verhina->p->m);
							return;
							}
						/// go to middle
							verhina->p->m->r=new V;
							verhina->p->m->r=verhina->l;
							verhina->p->m->r->p=verhina->p->m;
							verhina->p->r=NULL;

							upd_v(verhina->p);
							upd_v(verhina->p->m);
							return;
						/// go to middle
					}// in right son
				else
				{// in middle son
					if (allson(verhina->p->l))
								{
										verhina->m=new V;
										verhina->m=verhina->l;
										verhina->l=new V;
										verhina->l=verhina->p->l->r;
										verhina->l->p=verhina;

										verhina->p->l->r=NULL;

										upd_v(verhina);
										upd_v(verhina->p);
										return;
								}
							if (allson(verhina->p->r))
								{
								verhina->m=new V;
								verhina->m=verhina->p->r->l;
								verhina->m->p=verhina;

								verhina->p->r->l=new V;
								verhina->p->r->l=verhina->p->r->m;
								verhina->p->r->m=new V;
								verhina->p->r->m=verhina->p->r->r;
								verhina->p->r->r=NULL;

								upd_v(verhina);
								upd_v(verhina->p);
								upd_v(verhina->p->r);
								return;
								}
							/// go to left
								verhina->p->l->r=new V;
								verhina->p->l->r=verhina->l;
								verhina->p->l->r->p=verhina->p->l;

								verhina=verhina->p->l;
								verhina->p->m=new V;
								verhina->p->m=verhina->p->r;
								verhina->p->r=NULL;

								upd_v(verhina->p);
								upd_v(verhina->p->l);
								return;
							/// go to left
				}// in middle son

			}
			else
			{// in left son
				if (allson(verhina->p->m))
				{
					verhina->m=new V;
					verhina->m=verhina->p->m->l;
					verhina->m->p=verhina;

					verhina->p->m->l=new V;
					verhina->p->m->l=verhina->p->m->m;

					verhina->p->m->m=new V;
					verhina->p->m->m=verhina->p->m->r;
					verhina->p->m->r=NULL;

					upd_v(verhina);
					upd_v(verhina->p);
					upd_v(verhina->p->m);
					return;
				}
				if (allson(verhina->p->r))
				{
						verhina->m=new V;
						verhina->m=verhina->p->m->l;
						verhina->m->p=verhina;

						verhina->p->m->l=new V;
						verhina->p->m->l=verhina->p->m->m;

						verhina->p->m->m=new V;
						verhina->p->m->m=verhina->p->r->l;
						verhina->p->m->m->p=verhina->p->m;

						verhina->p->r->l=new V;
						verhina->p->r->l=verhina->p->r->m;

						verhina->p->r->m=new V;
						verhina->p->r->m=verhina->p->r->r;

						verhina->p->r->r=NULL;

						upd_v(verhina);
						upd_v(verhina->p);
						upd_v(verhina->p->m);
						upd_v(verhina->p->r);
						return;
				}
			/// go to left
				verhina->m=new V;
				verhina->m=verhina->p->m->l;
				verhina->m->p=verhina;

				verhina->r=new V;
				verhina->r=verhina->p->m->m;
				verhina->r->p=verhina;

				verhina->p->m=new V;

				verhina->p->m=verhina->p->r;
				verhina->p->r=NULL;

				upd_v(verhina);
				upd_v(verhina->p);
			return;
			/// go to left

			}// in left son
		}
		else // only two verh
		{
			if (verhina->field1>verhina->p->field1)
			{// in middle son
					if (allson(verhina->p->l))
					{
						verhina->m=new V;
						verhina->m=verhina->l;

						verhina->l=new V;
						verhina->l=verhina->p->l->r;
						verhina->l->p=verhina;
						verhina->p->l->r=NULL;

						upd_v(verhina);
						upd_v(verhina->p);
						return;
					}
					/////new cycle part
					verhina->p->l->r=new V;
					verhina->p->l->r=verhina->l;
					verhina=verhina->p->l;
					verhina->r->p=verhina;
					verhina->p->m=NULL;

					verhina->p->field1=verhina->field1;
					upd_v(verhina->p);
					/////new cycle part
			} // in middle son
			else
			{ // in left son

				if (allson(verhina->p->m))
				{
					verhina->m=new V;
					verhina->m=verhina->p->m->l;
					verhina->m->p=verhina;

					verhina->p->m->l=new V;
					verhina->p->m->l=verhina->p->m->m;

					verhina->p->m->m=new V;
					verhina->p->m->m=verhina->p->m->r;

					verhina->p->m->r=NULL;

					upd_v(verhina);
					upd_v(verhina->p);
					upd_v(verhina->p->m);

					return;
				}

				/////new cycle part
				verhina->m=new V;
				verhina->m=verhina->p->m->l;
				verhina->m->p=verhina;

				verhina->r=new V;
				verhina->r=verhina->p->m->m;
				verhina->r->p=verhina;

				verhina->p->m=NULL;

				verhina->p->field1=verhina->field1;
				upd_v(verhina->p);


				/////new cycle part
			} // in left son


		}
		verhina=verhina->p;
	}// cycle end


	if (verhina->p==NULL)
	{
		V *Gbuf;
		Gbuf=new V;
		Gbuf=verhina->l;

		root->l=new V;
		root->l=Gbuf->l;
		root->l->p=root;

		root->m=new V;
		root->m=Gbuf->m;
		root->m->p=root;

		root->r=new V;
		root->r=Gbuf->r;
		root->r->p=root;
		upd_v(root);
	}


			//////////////////// end end end the worst situation! we need delete not only 1 verh

		} // if (verhina->p->p->r==NULL) we have only two father
		else  // grandfather have 3 father
		{
			// grandfather have 3 father
			if(verhina->p->field1<verhina->p->p->field1)
			{
				// we are in left father
				if (allson(verhina->p->p->m))
							{// middle father have 3 son, we can give one!
								switch(l)
								{
								case 0:
									verhina->p->l=verhina->p->m;
									verhina->p->m=new V;
									verhina->p->m=verhina->p->p->m->l;
									verhina->p->m->p=verhina->p;
									break;
								case 1:
									verhina->p->m=verhina->p->p->m->l;
									verhina->p->m->p=verhina->p;
									break;
								}
									verhina->p->p->m->l=new V;
									verhina->p->p->m->l=verhina->p->p->m->m;
									verhina->p->p->m->m=new V;
									verhina->p->p->m->m=verhina->p->p->m->r;
									verhina->p->p->m->r=NULL;

								upd_v(verhina->p);
								upd_v(verhina->p->p);
								upd_v(verhina->p->p->m);
								return;
							} // if (allson(verhina->p->p->m))

				if (allson(verhina->p->p->r))
							{// right father have 3 son, we can give one!
								switch(l)
								{
								case 0:
									verhina->p->l=verhina->p->m;
									verhina->p->m=new V;
									verhina->p->m=verhina->p->p->m->l;
									verhina->p->m->p=verhina->p;
									break;
								case 1:
									verhina->p->m=verhina->p->p->m->l;
									verhina->p->m->p=verhina->p;
									break;
								}

								// from m
								verhina->p->p->m->l=verhina->p->p->m->m;
								verhina->p->p->m->m=new V;
								verhina->p->p->m->m=verhina->p->p->r->l;
								verhina->p->p->m->m->p=verhina->p->p->m;



								// from r
									verhina->p->p->r->l=new V;
									verhina->p->p->r->l=verhina->p->p->r->m;
									verhina->p->p->r->m=new V;
									verhina->p->p->r->m=verhina->p->p->r->r;
									verhina->p->p->r->r=NULL;

								upd_v(verhina->p);
								upd_v(verhina->p->p);
								upd_v(verhina->p->p->r);
								upd_v(verhina->p->p->m);

								return;
							} // if (allson(verhina->p->p->r))

				//if we are here, it way have all father with two son

				// go list to middle father

				///////////////////////////////////////////////////////////////////////////
				verhina->p->p->m->r=new V;
				verhina->p->p->m->r=verhina->p->p->m->m;
				verhina->p->p->m->m=new V;
				verhina->p->p->m->m=verhina->p->p->m->l;
				verhina->p->p->m->l=new V;

				switch(l)
												{
												case 0:
													verhina->p->p->m->l=verhina->p->m;
													verhina->p->p->m->l->p=verhina->p->p->m;
													break;
												case 1:
													verhina->p->p->m->l=verhina->p->l;
													verhina->p->p->m->l->p=verhina->p->p->m;
													break;
												}



												verhina->p->p->l=new V;
												verhina->p->p->l=verhina->p->p->m;
												verhina->p->p->m=new V;
												verhina->p->p->m=verhina->p->p->r;
												verhina->p->p->r=NULL;

												upd_v(verhina->p->p);
												upd_v(verhina->p->p->m);
												upd_v(verhina->p->p->l);
												return;
				//////////////////////////////////////////////////////////////////////////

			}
			else  // we are not in left father
			{
				if (verhina->p->field1<verhina->p->p->field2)
				{
					// we are in middle father


					if (allson(verhina->p->p->l))
						{// left father have 3 son, we can give one!
								switch(l)
								{
									case 0:
									verhina->p->l=verhina->p->p->l->r;
									verhina->p->l->p=verhina->p;
										break;
									case 1:
									verhina->p->m=verhina->p->l;
									verhina->p->l=new V;
									verhina->p->l=verhina->p->p->l->r;
									verhina->p->l->p=verhina->p;
										break;
								}

							verhina->p->p->l->r=NULL;

						upd_v(verhina->p);
						upd_v(verhina->p->p);
						upd_v(verhina->p->p->l);
						return;
						} // left father have 3 son, we can give one!


if (allson(verhina->p->p->r))
	  {// right father have 3 son, we can give one!
		switch(l)
			{
			 case 0:
			verhina->p->l=verhina->p->m;
			verhina->p->m=new V;
			verhina->p->m=verhina->p->p->r->l;
			verhina->p->m->p=verhina->p;
				break;
			case 1:
			verhina->p->m=verhina->p->p->r->l;
			verhina->p->m->p=verhina->p;
				break;
			}
		verhina->p->p->r->l=new V;
		verhina->p->p->r->l=verhina->p->p->r->m;
		verhina->p->p->r->m=new V;
		verhina->p->p->r->m=verhina->p->p->r->r;
		verhina->p->p->r->r=NULL;

		upd_v(verhina->p);
		upd_v(verhina->p->p);
		upd_v(verhina->p->p->r);
			return;
		} // if (allson(verhina->p->p->r))


//if we are here, it way have all father with two son

				// go list to left father

				///////////////////////////////////////////////////////////////////////////
					verhina->p->p->l->r=new V;
				switch(l)
												{
												case 0:
													verhina->p->p->l->r=verhina->p->m;
													verhina->p->p->l->r->p=verhina->p->p->l;
													break;
												case 1:
													verhina->p->p->l->r=verhina->p->l;
													verhina->p->p->l->r->p=verhina->p->p->l;
													break;
												}



												verhina->p->p->m=new V;
												verhina->p->p->m=verhina->p->p->r;
												verhina->p->p->r=NULL;

												upd_v(verhina->p->p);
												upd_v(verhina->p->p->l);
												return;
				//////////////////////////////////////////////////////////////////////////
				}
				else // we are in right father
				{
					// we are in right father


					if (allson(verhina->p->p->m))
								{// middle father have 3 son, we can give one!
									switch(l)
									{
									case 0:
									verhina->p->l=verhina->p->p->m->r;
									verhina->p->l->p=verhina->p;
										break;
									case 1:
									verhina->p->m=verhina->p->l;
									verhina->p->l=new V;
									verhina->p->l=verhina->p->p->m->r;
									verhina->p->l->p=verhina->p;
									break;
									}

								verhina->p->p->m->r=NULL;

									upd_v(verhina->p);
									upd_v(verhina->p->p);
									return;
								} // middle father have 3 son, we can give one!

					if (allson(verhina->p->p->l))
		{// left father have 3 son, we can give one!
			switch(l)
			{
			case 0:
			verhina->p->l=verhina->p->p->m->m;
			verhina->p->l->p=verhina->p;
				break;
			case 1:
			verhina->p->m=verhina->p->l;
			verhina->p->l=new V;
			verhina->p->l=verhina->p->p->m->m;
			verhina->p->l->p=verhina->p;
			break;
			}

			verhina->p->p->m->m=new V;
			verhina->p->p->m->m=verhina->p->p->m->l;
			verhina->p->p->m->l=new V;
			verhina->p->p->m->m=verhina->p->p->l->r;
			verhina->p->p->m->m->p=verhina->p->p->m;
			verhina->p->p->l->r=NULL;


			upd_v(verhina->p);
			upd_v(verhina->p->p);
			upd_v(verhina->p->p->l);
			upd_v(verhina->p->p->m);
			return;
		} // left father have 3 son, we can give one!



					//if we are here, it way have all father with two son

									// go list to middle father

									///////////////////////////////////////////////////////////////////////////
										verhina->p->p->m->r=new V;
									switch(l)
																	{
																	case 0:
																		verhina->p->p->m->r=verhina->p->m;
																		verhina->p->p->m->r->p=verhina->p->p->m;
																		break;
																	case 1:
																		verhina->p->p->m->r=verhina->p->l;
																		verhina->p->p->m->r->p=verhina->p->p->m;
																		break;
																	}


																	upd_v(verhina->p->p);
																	upd_v(verhina->p->p->m);
																	upd_v(verhina->p->p->l);
																	verhina->p->p->r=NULL;
																	return;
									//////////////////////////////////////////////////////////////////////////

				}
			}
		}

	}// we are not in root! (end)    ;)
} // end 2 way we have 2 lista in verh


}// over delV


void go_left(V *root)
{
	V *verhina=new V;
	V *buf=new V;
	verhina=root;


	if (!(notlist(verhina)))
	{
		if (verhina->p==NULL)
		{
			printf("empty tree\n");
		}
		else
		{
		printf("%d ",verhina->field1);
		}
	return;
	}

	if (verhina->l==NULL) {return;}
	buf=verhina;
		verhina=verhina->l;
	go_left(verhina);
	verhina=buf;
	if (verhina->m==NULL) {return;}
	buf=verhina;
		verhina=verhina->m;
	go_left(verhina);
	verhina=buf;
	if (verhina->r==NULL) {return;}
	buf=verhina;
		verhina=verhina->r;
	go_left(verhina);


}



int main()

{



V *root; // root



root=new V;



//if (root==NULL) {printf("memory allocation have been failed "); return 1;}

 /*  // output test


//root->field1=7;

// left
 root->l=new V;
 //root->l->field1=4;
// root->l->field2=5;
 root->l->p=root;

 root->l->l=new V;
 root->l->l->field1=3;
 root->l->l->p=root->l;

 root->l->m=new V;
 root->l->m->field1=4;
 root->l->m->p=root->l;

 root->l->r=new V;
 root->l->r->field1=5;
 root->l->r->p=root->l;


 //middle

 root->m=new V;
// root->m->field1=10;
 //root->m->field2=15;
 root->m->p=root;

 root->m->l=new V;
 root->m->l->field1=7;
 root->m->l->p=root->m;

 root->m->m=new V;
 root->m->m->field1=10;
 root->m->m->p=root->m;

 root->m->r=new V;
 root->m->r->field1=15;
 root->m->r->p=root->m;






 upd_v(root);
 upd_v(root->l);
 upd_v(root->m);
 */

  /*

 addV(6,root);
 addV(8,root);
 addV(12,root);
 addV(14,root);
 addV(18,root);
 addV(25,root);

 addV(15,root);




delV(18,root);





delV(8,root);


delV(12,root);

delV(14,root);

go_left(root);

 */





printf("all ok\n");



return 0;
}
