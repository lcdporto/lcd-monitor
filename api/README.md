Requisitos
==========

Dois focos principais:

* Autenticação
* Monitorização

Autenticação
------------

* autenticação de utilizadores
  * Suporte para "Single Sign On (SSO)"
* gestão de códigos por utilizador
* ativação/desativação remota (via web) do alarme
* atribuição de códigos temporários
* Pode ser delegada para um serviço externo
  * tem sempre que haver suporte para funcionar como backup

Monitorização
-------------

* Registar:
  * Alterações de estado
    * Sensores
    * Porta
* Alarmistca:
  * Fonte:
    * Sensores
      * Transição
      * Nivel
    * Porta
      * Transição
  * Tipos de alarmes:
    * Silenciosos
    * Sonoros
    * Remotos
