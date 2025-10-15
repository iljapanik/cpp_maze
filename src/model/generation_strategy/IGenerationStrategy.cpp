#include "IGenerationStrategy.h"

IGenerationStrategy::IGenerationStrategy(ErrorCallback errorCallback, RandomFunc randomFunc)
    : errorCallback_(errorCallback), randomFunc_(randomFunc)
{
}

bool IGenerationStrategy::BaseCheck(const IGenerationConfig &config)
{
    if (config.get_rows() <= 0 || config.get_cols() <= 0 || 
        config.get_rows() > 50 || config.get_cols() > 50)
    {
        emitError(ErrorType::IncorrectRowsCols);
        return false;
    }

    return true;
}

IGenerationStrategy::~IGenerationStrategy() = default;

void IGenerationStrategy::emitError(ErrorType error)
{
    if (errorCallback_)
    {
        errorCallback_(error);
    }
}
