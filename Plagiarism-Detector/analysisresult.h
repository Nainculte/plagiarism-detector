#ifndef ANALYSISRESULT_H
#define ANALYSISRESULT_H

#include <QString>
#include <QList>
#include <QHash>
#include <QVariant>
#include <QBrush>

class AnalysisResult
{
public:
    AnalysisResult();
    AnalysisResult(const QString &id1, const QString &id2);
    AnalysisResult(const float similarity, const QString &id1, const QString &id2,
                   const QHash<QString, QVariant> &metadata);
    AnalysisResult(const AnalysisResult & other);
    ~AnalysisResult();

    float similarity() const;
    QString id1() const;
    QString id2() const;
    QHash<QString, QVariant> metadata() const;
    QBrush color() const;

private:
    float _similarity;
    QString _id1;
    QString _id2;
    QHash<QString, QVariant> _metadata;
};

#endif // ANALYSISRESULT_H
