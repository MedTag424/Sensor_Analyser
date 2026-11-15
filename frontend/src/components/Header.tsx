import { Bell, Search } from "lucide-react";

export default function Header() {
  return (
    <header className="topbar">
      <div>
        <p className="breadcrumb">Monitoring / Overview</p>
        <h1>Dashboard</h1>
      </div>

      <div className="topbar-actions">
        <div className="search-box">
          <Search size={17} />
          <span>Search sensors...</span>
          <kbd>⌘ K</kbd>
        </div>

        <button className="icon-button" aria-label="Notifications">
          <Bell size={19} />
          <span className="notification-dot" />
        </button>

        <div className="avatar">AM</div>
      </div>
    </header>
  );
}
