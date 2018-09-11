#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QtCore/qsortfilterproxymodel.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qjsvalue.h>

class Person
{
    Q_GADGET
    Q_PROPERTY(QString author READ author WRITE setAuthor)
    Q_PROPERTY(QString title READ title WRITE setTitle)
public:
    Person(const QString& author ,const QString& title)
        :m_author(author),m_title(title){}
    Person() = default;
    Person(const Person& other)=default;
    Person& operator=(const Person& other)=default;

    const QString& author() const { return m_author; }
    void setAuthor(const QString &author) { m_author = author; }
    const QString& title() const { return m_title; }
    void setTitle(const QString &title) { m_title = title; }

private:
    QString m_author;
    QString m_title;
};

class SortFilterProxyModel : public QSortFilterProxyModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QObject *source READ source WRITE setSource)

    Q_PROPERTY(QByteArray sortRole READ sortRole WRITE setSortRole)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder)

    Q_PROPERTY(QByteArray filterRole READ filterRole WRITE setFilterRole)
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString)
    Q_PROPERTY(FilterSyntax filterSyntax READ filterSyntax WRITE setFilterSyntax)

    Q_PROPERTY(QAbstractItemModel* model READ model)
    Q_DISABLE_COPY(SortFilterProxyModel)

    Q_ENUMS(FilterSyntax)

public:
    explicit SortFilterProxyModel(QObject *parent = 0);

    QObject *source() const;
    void setSource(QObject *source);

    QByteArray sortRole() const;
    void setSortRole(const QByteArray &role);

    void setSortOrder(Qt::SortOrder order);

    QByteArray filterRole() const;
    void setFilterRole(const QByteArray &role);

    QString filterString() const;
    void setFilterString(const QString &filter);

    enum FilterSyntax {
        RegExp,
        Wildcard,
        FixedString
    };

    FilterSyntax filterSyntax() const;
    void setFilterSyntax(FilterSyntax syntax);

    int count() const;
    Q_INVOKABLE QJSValue get(int index) const;

    void classBegin();
    void componentComplete();

    Q_SLOT void addPerson(const QString& author ,const QString& title)
    {

            const int newRow= m_model->rowCount();
            const Person newPerson(author,title);
            m_model->insertRow(newRow);
            m_model->setData(m_model->index(newRow,0),QVariant::fromValue(newPerson),Qt::EditRole);
        }
        QAbstractItemModel* model() const {return m_model;}

signals:
    void countChanged();


protected:
    int roleKey(const QByteArray &role) const;
    QHash<int, QByteArray> roleNames() const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    void fillDummyData(){
            addPerson(QStringLiteral("Albert"),QStringLiteral("Einstein"));
            addPerson(QStringLiteral("Robert"),QStringLiteral("Oppenheimer"));
            addPerson(QStringLiteral("Enrico"),QStringLiteral("Fermi"));
            addPerson(QStringLiteral("Szef"),QStringLiteral("Szefoski"));
        }

    bool m_complete;
    QByteArray m_sortRole;
    QByteArray m_filterRole;
    QAbstractItemModel* m_model;
};


#endif // SORTFILTERPROXYMODEL_H
