#include "analysisresult.h"

AnalysisResult::AnalysisResult()
    : _similarity(0.0), _id1(""), _id2(""), _metadata(QHash<QString, QVariant>())
{
}

AnalysisResult::AnalysisResult(const QString &id1, const QString &id2)
    : _similarity(0.0), _id1(id1), _id2(id2), _metadata(QHash<QString, QVariant>())
{
}

AnalysisResult::AnalysisResult(const float similarity, const QString &id1,
                               const QString &id2,
                               const QHash<QString, QVariant> &metadata)
    : _similarity(similarity), _id1(id1), _id2(id2), _metadata(metadata)
{
}

AnalysisResult::AnalysisResult(const AnalysisResult &other)
    : _similarity(other._similarity), _id1(other._id1), _id2(other._id2), _metadata(other._metadata)
{
}

AnalysisResult::~AnalysisResult()
{
}

float AnalysisResult::similarity() const
{
    return _similarity;
}

QString AnalysisResult::id1() const
{
    return _id1;
}

QString AnalysisResult::id2() const
{
    return _id2;
}

QHash<QString, QVariant> AnalysisResult::metadata() const
{
    return _metadata;
}
