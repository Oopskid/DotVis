#include "pch.h"
#include "ShaderPart.h"

using namespace DVF;

ShaderPart::~ShaderPart()
{
    destroyTag();
    terminateShader();
}

void ShaderPart::setTag(const std::string& newTag)
{
    destroyTag();

    tag = _strdup(tag);
}

bool ShaderPart::getFile(std::ifstream& in, const std::string& path, bool asContext)
{
    in.open(path);

    //Construct null terminated path tag
    if (asContext)
    {
        setTag(path);
    }

    return in.good();
}

size_t ShaderPart::fetchRaw(const std::string& path, BYTE** raw, bool asContext)
{
    std::ifstream in;
    if (getFile(in, path))
    {
        //Read till the end
        std::string buffer;
        char next;
        while (in.get(next).good())
        {
            buffer.push_back(next);
        }

        //Copy over
        *raw = new byte[buffer.size()];
        if (buffer.copy((char*)*raw, buffer.size()) != buffer.size())
        {
            delete[] *raw;
            *raw = nullptr;
            
            return NULL;
        }

        return buffer.size();
    }

    return NULL;
}

HRESULT ShaderPart::fetchRawCompile(const std::string& path, BYTE** raw, size_t& rawCount, LPCSTR model, LPCSTR name, ShaderBuild::ShaderComponents* compileRules, UINT flags, bool asContext, bool cache)
{
    HRESULT result = S_OK;

    //First get the file
    rawCount = fetchRaw(path, raw, false);

    setTag(name);

    //Failure
    if (rawCount == NULL || raw == nullptr) { destroyTag(); return NTE_NOT_FOUND; }

    //Return if already compiled/incapable
    if (!compileRules || isCompiled(path)) { return result; }

    //Compile and fetch bytecode
    ID3DBlob* compileBlob = nullptr;
    result = ShaderBuild::compileShader(&compileBlob, *raw, rawCount, *compileRules, model, name, flags);

    //Remove existing
    {
        delete[](*raw);
        *raw = nullptr;
        rawCount = NULL;
    }

    if (FAILED(result) || compileBlob == nullptr) { destroyTag(); DVXClear(compileBlob); return result; }
    
    //Send compiled bytecode
    {
        *raw = static_cast<BYTE*>(compileBlob->GetBufferPointer());
        rawCount = compileBlob->GetBufferSize();

        DVXClear(compileBlob);
    }

    //Cache in the same location as a precompiled file (if required)
    if (cache)
    {
        std::filesystem::path cachePath(path);
        cachePath.replace_extension(ShaderBuild::PRECOMPILE_EXT);

        std::ofstream cacheOut(cachePath);
        cacheOut.write((const char*)(*raw), rawCount);
        cacheOut.close();

        //Success is not required
    }

    return result;
}

bool ShaderPart::isCompiled(const std::string& path)
{
    std::filesystem::path pathBreakdown(path);

    return pathBreakdown.has_extension() && pathBreakdown.extension() == ShaderBuild::PRECOMPILE_EXT;
}

void ShaderPart::destroyTag()
{
    if (tag)
    {
        delete[] tag;
        tag = nullptr;
    }
}

void ShaderPart::terminateShader()
{
    //Simple for now
    DVXClear(shaderObj);
}

void DVF::ShaderPart::setShader(IUnknown* shader)
{
    shaderObj = shader;
}
