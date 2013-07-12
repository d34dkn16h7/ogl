#include "tools.h"
#include "program.h"
#include "geometry.h"
#include "renderer.h"

vector< GData* > Geometry::gData;

void Geometry::Load(string fSrc,string name) /// Load .obj model
{
    gPtr = Find(name);
    if(gPtr == nullptr)
    {
        gPtr = new GData();
        gPtr->idString = name;
        Tools::Token geoToken( Tools::File::LoadFile(fSrc) );/// ch == ' ' || ch == '\n' || ch == '\t' || ch == '/'
        vector<char> rules = {' ' , '\n' ,'\t' , '/'};
        vector<char> splitter = { '/'};
        geoToken.RemakeWithRules(rules,splitter);

        while( geoToken.Next() !=  Tools::Token::EndToken )
        {
            if( geoToken == "v" )
                gPtr->pVerticle( geoToken.GetNVec3() );

            if( geoToken == "vt" )
                gPtr->pTextureCoord( geoToken.GetNVec2() );

            if( geoToken == "f" )
            {
                while( geoToken.CanGNum() )
                {
                    gPtr->pElement( (GLuint)geoToken.GetNi() - 1 );
                    if(geoToken.Peek(1) == "/") /// is next splitter for texture index?
                    {
                        geoToken.Next(); /// Skip the '/' splitter
                        gPtr->pTextureIndex( (geoToken.GetNi() - 1) * 2 );
                    }
                }
            }
        }

        if(geoToken.tokens.size() > 2)
        {
            gData.push_back(gPtr);
            LinkData();
        }
        else
            cout << "Empty or corrupted model file : " << name <<  endl;
    }
}

GData* Geometry::Find(string sStr) /// Find a model ptr
{
    for(GData* val : gData)
        if(val->idString == sStr)
            return val;

    return nullptr;
}

void Geometry::LoadTexture(string imgPath) /// Laod and link texture
{
    if(gPtr != nullptr)
        if(gPtr->texture == 0)
        {
            if(Tools::Settings::TextureLoadModern)
            {
                gPtr->texture = SOIL_load_OGL_texture(imgPath.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
                if (0 == gPtr->texture)
                    cout << "SOIL loading error: " <<  SOIL_last_result() << endl;
            }
            else
            {
                int width, height;
                unsigned char* image;

                glGenTextures( 1, &gPtr->texture );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

                glGenerateMipmap( GL_TEXTURE_2D );

                glActiveTexture( GL_TEXTURE0 );
                glBindTexture( GL_TEXTURE_2D, gPtr->texture );
                image = SOIL_load_image( imgPath.c_str() , &width, &height, 0, SOIL_LOAD_RGB );
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image );
                SOIL_free_image_data( image );
            }
        }
}

void Geometry::LinkData() /// Link VAO + VBO + EBO
{
    gPtr->MakeData();

    glGenVertexArrays( 1, &gPtr->vao );
    glBindVertexArray( gPtr->vao );

    glGenBuffers( 1, &gPtr->vbo );
    glBindBuffer( GL_ARRAY_BUFFER , gPtr->vbo );
    glBufferData( GL_ARRAY_BUFFER , (gPtr->data.size() * sizeof( gPtr->data[0])), &gPtr->data[0],GL_STATIC_DRAW);

    GLuint vertexAttrib = Program::GetProgramIns("Model")->gAttrib("vertexIn");
    GLuint textureCoordAttrib = Program::GetProgramIns("Model")->gAttrib("textureCoordIn");

    const size_t dataSize = sizeof(GLfloat) * 5;

    glEnableVertexAttribArray( vertexAttrib );
    glVertexAttribPointer( vertexAttrib , 3, GL_FLOAT, GL_FALSE, dataSize ,  0 );

    glEnableVertexAttribArray( textureCoordAttrib );
    glVertexAttribPointer( textureCoordAttrib , 2, GL_FLOAT, GL_FALSE, dataSize , (GLvoid*)( sizeof(GLfloat) * 3 ) );

    /*gPtr->verticles.clear();
    gPtr->textureCoord.clear();
    gPtr->elementary.clear();
    gPtr->data.clear();*/
}

// GData
void GData::MakeData()
{
    int ni = 0;
    vec2 lastIndexed(0,0);
    elementCount = elementary.size();

    for(int i = 0;i < elementary.size();i++)
    {
        int vertexIndexer = elementary[i] * 3;
        data.push_back(verticles[vertexIndexer]);
        data.push_back(verticles[vertexIndexer + 1]);
        data.push_back(verticles[vertexIndexer + 2]);

        if (textureIndexer.size() > 0 && textureCoord.size() > 0) /// is indexed
        {
            //cout << " Indexed Coordinates" << endl;
            int textureIndexeri = textureIndexer[i];
            lastIndexed = vec2(textureCoord[textureIndexeri],textureCoord[textureIndexeri + 1]);
        }
        else if( ni < textureCoord.size() ) /// not indexed but has data
        {
            //cout << " Raw Coordinates" << endl;
            lastIndexed = vec2(textureCoord[ni],textureCoord[ni + 1]);
        }
        //else /// Push last indexed values
            //cout << " TextureMapped -> 0:0" << endl;
        data.push_back(lastIndexed.x);
        data.push_back(lastIndexed.y);

        ni += 2;
    }

    //cout << "Edges : " << elementCount << endl;
    //printInfo();
    //cout << "Data.size " << data.size() << endl;
}

void GData::printInfo()
{
    cout << " ------ " << endl;
    cout << "Verticles : " << verticles.size() / 3 << endl;
    cout << "Vertex Elements : " << elementary.size() << endl;
    cout << "Indexed Texture Coordinates : " << textureIndexer.size() << endl;
    cout << "Texture Coordinates : " << textureCoord.size() / 2 << endl;
    cout << " ------ " << endl;
}

void GData::printData()
{
    for (int i = 0; i < data.size();i += 5)
    {
        cout << "vertex "<< data[i] << endl;
        cout << "vertex "<< data[i + 1] << endl;
        cout << "vertex "<< data[i + 2] << endl;
        cout << "vertexTexture "<< data[i + 3] << endl;
        cout << "vertexTexture "<< data[i + 4] << endl;
    }
}

void GData::pTextureCoord(vec2 tcoord)
{
    textureCoord.push_back(tcoord.x);
    textureCoord.push_back(tcoord.y);
}

void GData::pVerticle(vec3 vertex)
{
    verticles.push_back(vertex.x);
    verticles.push_back(vertex.y);
    verticles.push_back(vertex.z);
}

void GData::pElement(GLuint val)
{
    elementary.push_back ( val );
}

void GData::pTextureIndex(GLuint val)
{
    textureIndexer.push_back ( val );
}

unsigned int GData::gEdgeCount() const
{
    return elementCount;
}

GLuint GData::gType() const
{
    return type;
}

GLuint GData::gVBO() const
{
    return vbo;
}

GLuint GData::gVAO() const
{
    return vao;
}

GLuint GData::gEBO() const
{
    return ebo;
}
