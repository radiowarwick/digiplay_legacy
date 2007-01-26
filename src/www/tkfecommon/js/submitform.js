function submitform(task, id) {
	document.mainForm.task.value = task;
	document.mainForm.rguid.value = id;
	document.mainForm.submit();
}

function addRealmSubmitForm(id) {
	document.mainForm.parentID.value = id;
	document.mainForm.submit();
}