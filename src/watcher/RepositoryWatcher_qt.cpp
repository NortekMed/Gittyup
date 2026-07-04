//
//          Copyright (c) 2017, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: François Revol
//

#include "RepositoryWatcher.h"
#include <QFileSystemWatcher>
#include <QMap>
#include <QStringList>
#include <QThread>
#include <poll.h>
#include <unistd.h>

namespace {

// FIXME: Include hidden and filter .git explicitly?
const QDir::Filters kFilters = (QDir::Dirs | QDir::NoDotAndDotDot);

} // namespace

class RepositoryWatcherPrivate : public QObject {
  Q_OBJECT

public:
  RepositoryWatcherPrivate(const git::Repository &repo,
                           QObject *parent = nullptr)
      : QObject(parent), mRepo(repo), mFSWatcher(parent) {
    connect(&mFSWatcher, &QFileSystemWatcher::directoryChanged, this,
            &RepositoryWatcherPrivate::directoryChanged);
    connect(&mFSWatcher, &QFileSystemWatcher::fileChanged, this,
            &RepositoryWatcherPrivate::fileChanged);
    watchWorkdir(mRepo.workdir());
    watchGitMetadata();
  }

  ~RepositoryWatcherPrivate() {}

  bool isValid() const { return true; }

  void directoryChanged(const QString &path) {
    if (isGitMetadataDirectory(path)) {
      watchGitMetadata();
      emit notificationReceived();
    } else if (!mRepo.isIgnored(path)) {
      // Start watching new directories.
      if (QDir(path).exists())
        watchWorkdir(path);
      emit notificationReceived();
    }
  }

  void fileChanged(const QString &path) {
    if (isGitMetadataPath(path))
      watchGitMetadata();

    emit notificationReceived();
  }

  void watchWorkdir(const QDir &dir) {
    mFSWatcher.addPath(dir.path().toUtf8());

    // Watch subdirs.
    foreach (const QString &name, dir.entryList(kFilters)) {
      QString path = dir.filePath(name);
      if (!mRepo.isIgnored(path))
        watchWorkdir(path);
    }
  }

  void watchGitDirectory(const QDir &dir, bool recursive) {
    if (!dir.exists())
      return;

    mFSWatcher.addPath(dir.path().toUtf8());

    if (!recursive)
      return;

    foreach (const QString &name, dir.entryList(kFilters))
      watchGitDirectory(QDir(dir.filePath(name)), true);
  }

  void watchGitMetadata() {
    QDir gitDir = mRepo.dir();
    watchGitDirectory(gitDir, false);

    foreach (const QString &path, QStringList({"HEAD", "index", "packed-refs"}))
      mFSWatcher.addPath(gitDir.filePath(path).toUtf8());

    foreach (const QString &path,
             QStringList({"refs", "refs/heads", "refs/remotes", "refs/tags",
                          "logs", "logs/refs", "logs/refs/heads",
                          "logs/refs/remotes"}))
      watchGitDirectory(QDir(gitDir.filePath(path)), true);
  }

  bool isGitMetadataDirectory(const QString &path) const {
    QString relative = mRepo.dir().relativeFilePath(path);
    return relative == "." || relative == "refs" ||
           relative.startsWith("refs/") || relative == "logs" ||
           relative == "logs/refs" || relative.startsWith("logs/refs/heads") ||
           relative.startsWith("logs/refs/remotes");
  }

  bool isGitMetadataPath(const QString &path) const {
    QString relative = mRepo.dir().relativeFilePath(path);
    return relative == "HEAD" || relative == "index" ||
           relative == "packed-refs" || relative.startsWith("refs/") ||
           relative == "logs/HEAD" || relative == "logs/refs/heads" ||
           relative.startsWith("logs/refs/heads/") ||
           relative == "logs/refs/remotes" ||
           relative.startsWith("logs/refs/remotes/");
  }

signals:
  void notificationReceived();

private:
  git::Repository mRepo;
  QFileSystemWatcher mFSWatcher;
};

RepositoryWatcher::RepositoryWatcher(const git::Repository &repo,
                                     QObject *parent)
    : QObject(parent), d(new RepositoryWatcherPrivate(repo, this)) {
  init(repo);
  connect(d, &RepositoryWatcherPrivate::notificationReceived, &mTimer,
          static_cast<void (QTimer::*)()>(&QTimer::start));
}

RepositoryWatcher::~RepositoryWatcher() {}

#include "RepositoryWatcher_qt.moc"
