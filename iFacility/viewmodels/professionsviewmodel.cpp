#include "professionsviewmodel.h"

ProfessionsViewModel::ProfessionsViewModel(QObject *parent) : QStandardItemModel(parent) {

}

void ProfessionsViewModel::invalidateData() {
    beginResetModel();

    clear();
    QStandardItemModel::setHeaderData(0, Qt::Orientation::Horizontal, "Professions");
    QStandardItem *rootNode = invisibleRootItem();
    foreach (auto prof, Database::instance()->professions()) {
        QStandardItem *profNode = new QStandardItem("Profession: " + prof.title());
        QStandardItem *profUID = new QStandardItem("PID: " + prof.pID().toString());
        QStandardItem *currentWorkers = new QStandardItem("Current workers");
        QStandardItem *availableWorkers = new QStandardItem("Available workers");
        foreach(auto worker, Database::instance()->getUsersByProfession(prof.pID())) {
            QStandardItem *workerNode = new QStandardItem(worker->getFullNameShortForm());
            UserProfession up;
            foreach (auto uProf, worker->getProfessions()) {
                if (uProf.getProfession() == prof.pID()) {
                   up = uProf;
                }
            }
            QStandardItem *workerRank = new QStandardItem(tr("%1 rank").arg(up.getRank()));
            QStandardItem *acqDateNode = new QStandardItem(
                        up.getAcquiredDate().toString(Qt::DateFormat::SystemLocaleShortDate));
            workerNode->appendRow(workerRank);
            workerNode->appendRow(acqDateNode);
            if (worker->getCurrentProfession() == prof.pID()) {
                currentWorkers->appendRow(workerNode);
            }
            else {
                availableWorkers->appendRow(workerNode);
            }
        }

        profNode->appendRow(profUID);
        profNode->appendRow(currentWorkers);
        profNode->appendRow(availableWorkers);
        rootNode->appendRow(profNode);
    }

    endResetModel();
}
