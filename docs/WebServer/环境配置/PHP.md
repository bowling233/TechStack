> From: [Configure PHP on a Debian or Ubuntu instance – DreamHost Knowledge Base](https://help.dreamhost.com/hc/en-us/articles/215231198-Configure-PHP-on-a-Debian-or-Ubuntu-instance)
> [Site Unreachable](https://www.theserverside.com/blog/Coffee-Talk-Java-News-Stories-and-Opinions/Nginx-PHP-FPM-config-example)

## 在 Debian 11 上

使用 Ubuntu 教程提供的 PPA 源将出现问题：

解决办法：[php - Couldn't find any package by glob 'php8.0' in debian - Stack Overflow](https://stackoverflow.com/questions/66158318/couldnt-find-any-package-by-glob-php8-0-in-debian)

For Debian Buster (10) and Debian Bullseye (11)

With root access:

```bash
apt update && apt install -y wget gnupg2 lsb-release
wget https://packages.sury.org/php/apt.gpg && apt-key add apt.gpg
echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/php.list
apt update && apt install -y php8.1
php -v # Outputs "PHP 8.1.3 ..."
```

